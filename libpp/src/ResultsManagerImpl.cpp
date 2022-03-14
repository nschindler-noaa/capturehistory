/*
 * ResultsManagerImpl.cpp
 */

#include <float.h>

#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

#include <QStringList>
#include <qcombobox.h>
#include <qdir.h>
#include <qtextstream.h>
#include <qstatusbar.h>
#include <qaction.h>
#include <qtabwidget.h>
#include <qlineedit.h>
#include <qregexp.h>
#include <qapplication.h>
#include <QMessageBox>
#include <qdatetime.h>
#include <QPrinter>
#include <QPainter>
#include <QVector>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTextEdit>
#include <QPrintDialog>
#include <QTextCursor>
#include <QTextTable>
#include <QTextFrame>
#include <QResource>
#include <QStatusBar>
#include <QPair>

#include <ArrayDefs.h>
#include <StringTok.h>
#include <StringManip.h>
#include <TaggingData.h>
#include <SurphData.h>
#include <CjsEstimates.h>
#include <CjsStatistics.h>
#include <CjsReport.h>
#include <CjsUnformattedReport.h>
#include <ParseError.h>
#include <PPObs.h>
#include <PPTag.h>
#include <PPRecap.h>
#include <Sites.h>
#include <Detector.h>
#include <DateConverter.h>
#include <Site.h>

#include "ResultsManagerImpl.h"
#include "PitProSettings.h"
#include "PPSystemSettings.h"
#include "PitProUtilities.h"
#include "ArrayDefs.h"
#include "Statistics.h"
#include "charutil.h"
#include "PPErrors.h"
#include "PPRunInfo.h"
//#include "PPStyleSheet.h"
#include "PPData.h"

using std::string;
using std::stringstream;
using std::vector;
using std::ifstream;
using std::pair;
using std::less;

using namespace cbr;

typedef QPair<QString, QString> StringPair;
typedef QPair<QString, QStringList> StringVectorPair;

/*
 *  Constructs a ResultsManagerImpl which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'
 */
ResultsManagerImpl::ResultsManagerImpl(QWidget* parent, const QString name, Qt::WindowFlags fl)
: QMainWindow(parent, fl)
{
    p = 3;
    staleSummaryPage = true;
    staleSurphPage = true;
    staleErrorsPage = true;
    staleTtPage = true;
    staleCjsPage = true;
    staleDataPage = true;
    setObjectName(name);
    setupUi(this);

    // add groups to the combo list
    updateGroupCombo();

    PPSystemSettings& systemSettings = PPSystemSettings::getInstance();
    showLambdaCB->setChecked(systemSettings.isChecked(PPSystemSettings::ShowLambda));
    oneTableCjsCB->setChecked(systemSettings.isChecked(PPSystemSettings::OneTableCjs));
    trackerDetailCheckBox->setChecked(systemSettings.isChecked(PPSystemSettings::ShowTrackerDetails));

    // make certain displays no wrap
    cjsTextEdit->setLineWrapMode(QTextEdit::NoWrap);
    errorsTextEdit->setLineWrapMode(QTextEdit::NoWrap);
    ttTextEdit->setLineWrapMode(QTextEdit::NoWrap);

    PitProSettings& settings = PitProSettings::getInstance();
    QStringList searchPaths;
    searchPaths << settings.getValue(PitProSettings::DataDir);
    searchPaths << settings.getValue(PitProSettings::OutputDir);
    summaryTextBrowser->setSearchPaths(searchPaths);
    dataTextBrowser->setSearchPaths(searchPaths);

    connect(summaryTextBrowser, SIGNAL(anchorClicked(const QUrl&)), SLOT(doSummaryAnchorClicked(const QUrl&)));
    connect(dataTextBrowser, SIGNAL(anchorClicked(const QUrl&)), SLOT(doDataAnchorClicked(const QUrl&)));
    summaryTextBrowser->setOpenLinks(false);
    dataTextBrowser->setOpenLinks(false);

    actionSave->setEnabled(false);

    // signals and slots connections
    connect(tabWidget, SIGNAL(currentChanged(QWidget*)), this, SLOT(currentTabChanged(QWidget*)));
    connect(groupCombo, SIGNAL(activated(const QString&)), this, SLOT(setGroup(const QString&)));
    connect(backButton, SIGNAL(clicked()), this, SLOT(summaryPageHome()));
    connect(goButton, SIGNAL(clicked()), this, SLOT(trackPitCode()));
    connect(dataBackButton, SIGNAL(clicked()), this, SLOT(dataSummaryPageHome()));
    connect(actionExit, SIGNAL(activated()), this, SLOT(close()));
    connect(ttRunCombo, SIGNAL(activated(const QString&)), this, SLOT(updateTtPage(const QString&)));
    connect(errorRunCombo, SIGNAL(activated(const QString&)), this, SLOT(updateErrorsPage(const QString&)));
    connect(actionCovariance_matrix, SIGNAL(activated()), this, SLOT(doCovarianceMatrix()));
    connect(actionCJS_Data, SIGNAL(activated()), this, SLOT(doCjsData()));
    connect(actionTravel_Time_data, SIGNAL(activated()), this, SLOT(doTTData()));
    connect(actionPrint, SIGNAL(activated()), this, SLOT(doPrint()));
    connect(actionSave, SIGNAL(activated()), this, SLOT(doSave()));
    connect(trackerDetailCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onTrackerDetailChecked(int)));
    connect(oneTableCjsCB, SIGNAL(stateChanged(int)), this, SLOT(onShowOneTableCjsChecked(int)));
    connect(showLambdaCB, SIGNAL(stateChanged(int)), this, SLOT(onShowLambdaChecked(int)));

    // formatting

    // headings and body text
    const int fontSize = 8;
    QString fontFamily("MS Shell Dlg 2");
    fixedFont = QFont("Courier", fontSize, QFont::Normal);

    bodyText.setFont(QFont(fontFamily, fontSize, QFont::Normal));
    boldText.setFont(QFont(fontFamily, fontSize, QFont::Bold));
    italicText.setFont(QFont(fontFamily, fontSize, QFont::Normal, true));
    fixedText.setFont(fixedFont);
    heading1.setFont(QFont(fontFamily, fontSize + 4, QFont::Bold));
    heading1.setUnderlineStyle(QTextCharFormat::SingleUnderline);
    heading2.setFont(QFont(fontFamily, fontSize + 2, QFont::Bold));
    heading3.setFont(QFont(fontFamily, fontSize, QFont::Bold));


    // tables
    tableFormat.setCellPadding(5);
    tableFormat.setLeftMargin(10);

    QColor headerBg;
    headerBg.setNamedColor("#CCFFFF");

    tableHeaderFormat.setBackground(headerBg);
    tableHeaderFormat.setPadding(3);
    tableHeaderFormat.setFontWeight(QFont::Bold);

    tableDataFormat.setFontPointSize(fontSize);
    tableDataFormat.setRightPadding(10);
    tableDataFormat.setLeftPadding(4);

    leftTbf.setAlignment(Qt::AlignLeft);

    centerTbf.setAlignment(Qt::AlignCenter);

    rightTbf.setAlignment(Qt::AlignRight);

    // frames and blocks
    frameFormat.setMargin(10);
    sectionTbf.setTopMargin(20);
    paragraphTbf.setTopMargin(10);
    paragraphTbf.setBottomMargin(0);
    indentedTbf.setTopMargin(5);
    indentedTbf.setLeftMargin(10);
    linebreakTbf.setTopMargin(1);
    linebreakTbf.setBottomMargin(0);
    indentedLinebreakTbf.setTopMargin(1);
    indentedLinebreakTbf.setBottomMargin(0);
    indentedLinebreakTbf.setLeftMargin(10);

    // list format
    listFormat.setStyle(QTextListFormat::ListDisc);
    listFormat.setIndent(0);

    summaryTextBrowser->textCursor().currentFrame()->setFrameFormat(frameFormat);
    dataTextBrowser->textCursor().currentFrame()->setFrameFormat(frameFormat);
    cjsTextEdit->textCursor().currentFrame()->setFrameFormat(frameFormat);
    ttTextEdit->textCursor().currentFrame()->setFrameFormat(frameFormat);
    trackerTextEdit->textCursor().currentFrame()->setFrameFormat(frameFormat);
}

/*
 *  Destroys the object and frees any allocated resources
 */
ResultsManagerImpl::~ResultsManagerImpl() {

}

void ResultsManagerImpl::outputDirChanged(const QString&) {
    updateGroupCombo();
    setStale(true);
}

void ResultsManagerImpl::doPrint() {

    // get the textedit for the current page
    QTextEdit* textEdit;
    QWidget* current = tabWidget->currentWidget();
    const QString& name = current->objectName();
    if (name.compare("data") == 0)
        textEdit = dataTextBrowser;
    else if (name.compare("errors") == 0)
        textEdit = errorsTextEdit;
    else if (name.compare("travelTime") == 0)
        textEdit = ttTextEdit;
    else if (name.compare("cjs") == 0)
        textEdit = cjsTextEdit;
    else if (name.compare("tracker") == 0)
        textEdit = trackerTextEdit;
    else
        textEdit = summaryTextBrowser;

    QPrinter printer;

    QPrintDialog *printDialog = new QPrintDialog(&printer, this);
    printDialog->setWindowTitle(tr("Print Document"));
    if (textEdit->textCursor().hasSelection())
        printDialog->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (printDialog->exec() != QDialog::Accepted)
        return;

    textEdit->print(&printer);
}

void ResultsManagerImpl::doSave() {
    QWidget* current = tabWidget->currentWidget();
    const QString& type = current->objectName();

    QString output;
    if (!type.compare("cjs")) {
        output = cjsTextEdit->toPlainText();
    } else if (!type.compare("travelTime")) {
        output = ttTextEdit->toPlainText();
    }

    QString filter = "Text (*.txt)";

    const QString& group = groupCombo->currentText();
    QString fileName = group + "_" + type + ".csv";
    saveFile(fileName, output, filter);
}

void ResultsManagerImpl::saveFile(const QString& fileName, const QString& output, const QString& filter) {
    PitProSettings& settings = PitProSettings::getInstance();
    QString filePath = settings.getOutFilePath(fileName);

    QString selectedFileName = QFileDialog::getSaveFileName(this, tr("Save File"),
            filePath,
            filter);

    if (!selectedFileName.isEmpty()) {
        QFile file(selectedFileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

            QTextStream out(&file);
            out << output;

            file.close();
        }
    }
}

void ResultsManagerImpl::setStale(bool rhs) {
    staleSummaryPage = rhs;
    staleSurphPage = rhs;
    staleErrorsPage = rhs;
    staleTtPage = rhs;
    staleCjsPage = rhs;
    staleDataPage = rhs;
    updateCurrentPage();
}

/*
 *
 */
void ResultsManagerImpl::setGroup(const QString& group) {
    updateGroupCombo();
    groupCombo->setCurrentIndex(groupCombo->findText(group));//Text(group);
    setStale(true);
    updateCurrentPage();
}

/*
 *
 */
void ResultsManagerImpl::currentTabChanged(QWidget* current) {
    if (!current)
        current = tabWidget->currentWidget();
    const QString& name = current->objectName();
    actionSave->setEnabled(!name.compare("travelTime") || !name.compare("cjs"));

    updateCurrentPage(current);
}

void ResultsManagerImpl::updateCurrentPage(QWidget* current) {
    if (!current)
        current = tabWidget->currentWidget();
    const QString& name = current->objectName();

    QTextEdit* textEdit = 0;
    if (name.compare("summary") == 0) {
        textEdit = summaryTextBrowser;
        updateSummaryPage();
    } else if (name.compare("errors") == 0)
        updateErrorsPage(QString::null);
    else if (name.compare("travelTime") == 0)
        updateTtPage(QString::null);
    else if (name.compare("cjs") == 0)
        updateCjsPage();
    else if (name.compare("data") == 0)
        updateDataPage();

    if (textEdit) {
        textEdit->setTextCursor(textEdit->document()->rootFrame()->firstCursorPosition());
        textEdit->ensureCursorVisible();
    }

}

// add groups from current output directory to the combo list

void ResultsManagerImpl::updateGroupCombo() {
    QStringList suffixes;
    PitProSettings& settings = PitProSettings::getInstance();
    suffixes += settings.getValue(PitProSettings::ConfigSuffix);
    suffixes += settings.getValue(PitProSettings::SurphSuffix);
    suffixes += settings.getValue(PitProSettings::ErrorSuffix);
    suffixes += settings.getValue(PitProSettings::DdSuffix);
    suffixes += settings.getValue(PitProSettings::TtSuffix);
    suffixes += settings.getValue(PitProSettings::SeqSuffix);

    QString outputDir = settings.getValue(PitProSettings::OutputDir);
    QStringList groups = PitProUtilities::getResultsGroups(outputDir, suffixes);
//    groupCombo->clearEdit();
    groupCombo->clear();
    groupCombo->addItems(groups);
    groupCombo->setCurrentIndex(0);
}

void ResultsManagerImpl::summaryPageHome() {
    staleSummaryPage = true;
    updateSummaryPage();
}

void ResultsManagerImpl::dataSummaryPageHome() {
    staleDataPage = true;
    updateDataPage();
}

void ResultsManagerImpl::updateSummaryPage() {

    if (staleSummaryPage) {
        // make the group combo current
        QString group = groupCombo->currentText();

        QTextCursor cursor = clearFrame(summaryTextBrowser);

        if (group.isEmpty())
            cursor.insertText("No group selected.", boldText);
        else {
            cursor.insertText("Summary Report for \"" + group + "\"", heading1);

            updateGroupCombo();
            if (!group.isEmpty())
                groupCombo->setCurrentIndex(groupCombo->findText(group));//Text(group);
            else {
                groupCombo->setCurrentIndex(0);
                group = groupCombo->currentText();
            }

            QStringList prefixes;
            bool combined = false;
            PPRunInfo& runInfo = PPRunInfo::instance();
            QString fileName = runInfo.getConfigFileName(group);
            if (runInfo.load(group)) {
                QStringList runNames = runInfo.getRunNames();
                runNames.append(prefixes);
                prefixes = runNames;
//                prefixes.insert(prefixes.begin(), runNames.begin(), runNames.end());
                combined = runInfo.isCombined();
            }

            if (prefixes.isEmpty())
                prefixes.append(group);

            if (combined)
                getCombinedSummaryOutput(cursor, group);

            for (QStringList::const_iterator it = prefixes.begin(); it != prefixes.end(); ++it) {
                const QString& prefix = *it;
                getOutputByPrefix(cursor, prefix, combined);
            }
        }
        staleSummaryPage = false;
    }
}

void ResultsManagerImpl::updateErrorsPage(const QString& run) {
    if (!run.isEmpty())
        staleErrorsPage = true;

    if (staleErrorsPage) {
        QTextCursor cursor = clearFrame(errorsTextEdit);

        if (groupCombo->currentText().isEmpty())
            cursor.insertText("No group selected.", boldText);
        else {
            QString prefix = groupCombo->currentText();
            QStringList prefixes;
            PPRunInfo& runInfo = PPRunInfo::instance();
            if (runInfo.load(prefix)) {
                QStringList runNames = runInfo.getRunNames();
                runNames.append(prefixes);
                prefixes = runNames;
//                prefixes.insert(prefixes.begin(), runNames.begin(), runNames.end());
            }
            if (prefixes.size() == 0)
                prefixes.push_back(prefix);

            // handle run combo
            QString currentRun;
            if (!run.isEmpty())
                currentRun = run;
            else {
                errorRunCombo->clear();
                for (QStringList::const_iterator it = prefixes.begin(); it != prefixes.end(); ++it) {
                    errorRunCombo->addItem(*it);
                }
                errorRunCombo->setEnabled(prefixes.size() != 1);
                currentRun = prefixes.front();
            }

            // parse the error file
            QString displayPrefix = prefixes.front();
            statusBar()->showMessage(QString("Loading errors file for run \"%1\"...").arg(currentRun));
//            statusBar()->message("Loading errors file for run \"" + currentRun + "\"...");

            createErrorReport(cursor, currentRun);

            statusBar()->clearMessage();
//            statusBar()->clear();
        }

    }
}

// summarize the travel time results

void ResultsManagerImpl::updateTtPage(const QString& run) {
    if (!run.isEmpty())
        staleTtPage = true;

    if (staleTtPage) {
        QTextCursor cursor = clearFrame(ttTextEdit);
        ttDataTextEdit.clear();
        QTextCursor dataCursor = ttDataTextEdit.textCursor();

        if (groupCombo->currentText().isEmpty()) {
            cursor.insertText("No group selected.", boldText);
            dataCursor.insertText("No group selected.", boldText);
        } else {

            QString group = groupCombo->currentText();
            QStringList prefixes;
            PPRunInfo& runInfo = PPRunInfo::instance();
            if (runInfo.load(group)) {
                QStringList runNames = runInfo.getRunNames();
                runNames.append(prefixes);
                prefixes = runNames;
//                prefixes.insert(prefixes.begin(), runNames.begin(), runNames.end());
            }

            if (prefixes.size() == 0)
                prefixes.push_back(group);

            QString currentRun;
            if (!run.isEmpty())
                currentRun = run;
            else {
                ttRunCombo->clear();
                for (QStringList::const_iterator it = prefixes.begin(); it != prefixes.end(); ++it) {
                    ttRunCombo->addItem(*it);
                }
                ttRunCombo->setEnabled(prefixes.size() != 1);
                currentRun = prefixes.front();
            }

            statusBar()->showMessage("Loading travel time data for run \"" + group + "\"...");

            PitProSettings& settings = PitProSettings::getInstance();
            QString fileName(currentRun + "." + settings.getValue(PitProSettings::DdSuffix));
            QString path = settings.getOutFilePath(fileName);

            ifstream in(path.toStdString().data());
            if (!in.is_open()) {
                cursor.insertText("No travel time results found.", boldText);
                dataCursor.insertText("No travel time results found.", boldText);
                return;
            }

            // parse header line
            QStringList headers;
            string line;
            if (getline(in, line)) {
                bool bit = false;
                QStringList tokens;
//                StringVector tokens;
                stringTok(tokens, QString(line.data()), " ");
                for (int i = 0; i < tokens.count(); i++)
                {
                    if (i == 0) {
                        if (tokens.at(i).compare("pitcode") != 0)
                            break;
                    } else {
                        bit = !bit;
                        if (bit)
                            headers.push_back(tokens.at(i));
                    }
                }
                /*
                for (StringVector::iterator it = tokens.begin(); it != tokens.end(); ++it) {
                    if (it == tokens.begin()) {
                        if ((*it).compare("pitcode") != 0)
                            break;
                    } else {
                        bit = !bit; // get every other token
                        if (bit)
                            headers.push_back(*it);
                    }
                }*/
            }

            // parse the travel time data
            if (headers.size() == 0) {
                cursor.insertText("No header found in travel time data file.", boldText);
                dataCursor.insertText("No header found in travel time data file.", boldText);
                return;
            }

            int numSites = headers.size();
            Matrix<DoubleVector> ttMatrix(numSites, numSites);
            while (getline(in, line)) {
                QStringList tokens;
//                StringVector tokens;
                stringTok(tokens, QString(line.data()), " ");

                DoubleVector detDates;
                int numDetDates = (numSites * 2 - 1);
                for (int i = 0; i < numDetDates; ++i) {
                    detDates[i] = tokens.at(i+1).toDouble();//fromString<double> (tokens[i + 1]);
                }

                // build travel time matrix
                for (int i = 0; i < detDates.size(); i += 2) {
                    double dd1 = detDates.at(i);
                    for (int j = i + 1; j < detDates.size(); j += 2) {
                        double dd2 = detDates.at(j);
                        if (dd1 != 0 && dd2 != 0) {
                            int row = i / 2;
                            int col = (j / 2) + 1;
                            ttMatrix(row, col).push_back(dd2 - dd1);
                        }
                    }
                }
            }
            in.close();

            createTTTableReport(cursor, headers, ttMatrix, currentRun);
            createTTDataReport(dataCursor, headers, ttMatrix, currentRun);
        }

        statusBar()->clearMessage();
        staleTtPage = false;
    }
}

void ResultsManagerImpl::updateCjsPage() {
    if (staleCjsPage) {
        QTextCursor cjsCursor = clearFrame(cjsTextEdit);
        cjsDataTextEdit.clear();
        QTextCursor cjsDataCursor = cjsDataTextEdit.textCursor();
        covarTextEdit.clear();
        QTextCursor covarCursor = covarTextEdit.textCursor();

        if (groupCombo->currentText().isEmpty()) {
            cjsCursor.insertText("No group selected.", boldText);
            cjsDataCursor.insertText("No group selected.", boldText);
            covarCursor.insertText("No group selected.", boldText);
        } else {
            QString group = groupCombo->currentText();
            statusBar()->showMessage("Loading capture history file for run \"" + group + "\"...");

            PitProSettings& settings = PitProSettings::getInstance();
            QString fileName = group + "." + settings.getValue(PitProSettings::SurphSuffix);
            QString filePath = settings.getOutFilePath(fileName);
            ifstream surphInput(filePath.toStdString().data());
            if (!surphInput) {
                cjsCursor.insertText("No capture history data found.", errorText);
                cjsDataCursor.insertText("No capture history data found.", errorText);
                covarCursor.insertText("No capture history data found.", errorText);
                return;
            }
            try {
                // Set up the statistics
                surph::SurphData surphData(surphInput, filePath);

                QList<CjsStatistics*> statistics;//(surphData.numPopulations());
                int numPop = surphData.numPopulations();
                for (int i = 0; i < numPop; ++i)
                    statistics.append(new CjsStatistics(surphData.captureHistoryMap(i), surphData.numPeriods()));

                // CJS estimates
                QList<CjsEstimates*> estimates;//(surphData.numPopulations());
                for (int i = 0; i < numPop; ++i) {
                    estimates.append(new CjsEstimates(*statistics[i]));
                }

                cjsCursor.beginEditBlock();
                createCjsReport(cjsCursor, surphData, estimates, group);
                cjsCursor.endEditBlock();

                createCjsDataReport(cjsDataCursor, surphData, estimates, group);
                createCovarianceReport(covarCursor, surphData, group);
            } catch (ParseError& err) {
                stringstream ss;
                ss << err;
                cjsCursor.insertText(QString(ss.str().c_str()), errorText);
                cjsDataCursor.insertText(QString(ss.str().c_str()), errorText);
                covarCursor.insertText(QString(ss.str().c_str()), errorText);
            } catch (ErrorObject& err) {
                stringstream ss;
                ss << err;
                cjsCursor.insertText(QString(ss.str().c_str()), errorText);
                cjsDataCursor.insertText(QString(ss.str().c_str()), errorText);
                covarCursor.insertText(QString(ss.str().c_str()), errorText);
            }

        }

        statusBar()->clearMessage();
        staleCjsPage = false;
    }
}

void ResultsManagerImpl::updateDataPage() {
    if (staleDataPage) {
        QTextCursor cursor = clearFrame(dataTextBrowser);
        if (groupCombo->currentText().isEmpty())
            cursor.insertText("No group selected.", boldText);
        else {
            QString group = groupCombo->currentText();
            createDataSummary(cursor, group);
        }
        statusBar()->clearMessage();
        staleDataPage = false;
    }
}

void ResultsManagerImpl::createDataSummary(QTextCursor& cursor, const QString &prefix) {
    cursor.insertText("Data Input Report for \"" + prefix + "\"", heading1);

    PPRunInfo& runInfo = PPRunInfo::instance();
    if (!runInfo.load(prefix)) {
        cursor.insertBlock(paragraphTbf);
        cursor.insertText("Can't find run configuration information.", boldText);
    } else {
        RunConfigVector runConfig = runInfo.getRunConfig();
        for (RunConfigVector::const_iterator it = runConfig.begin(); it != runConfig.end(); ++it) {
            const RunConfigItem& runItem = *it;
            createDataSummaryReport(cursor, runItem);
        }
    }
}

void ResultsManagerImpl::createDataSummaryReport(QTextCursor& cursor, const RunConfigItem& runItem) {
//    stringstream ss;

    cursor.beginEditBlock();
    cursor.insertBlock(sectionTbf);
    cursor.insertText("Input files for \"" + runItem.name + "\":", heading2);

    cursor.insertBlock(paragraphTbf);
    QTextTable* table = cursor.insertTable(5, 4, tableFormat);
    for (int i = 0; i < table->columns(); ++i)
        table->cellAt(0, i).setFormat(tableHeaderFormat);
    for (int i = 0; i < table->rows(); ++i)
        table->cellAt(i, 0).setFormat(tableHeaderFormat);

    table->cellAt(0, 1).firstCursorPosition().insertText("Name");
    table->cellAt(0, 2).firstCursorPosition().insertText("Size (bytes)");
    table->cellAt(0, 3).firstCursorPosition().insertText("Last Modified Date");

    table->cellAt(1, 0).firstCursorPosition().insertText("Observations");
    table->cellAt(2, 0).firstCursorPosition().insertText("Tags");
    table->cellAt(3, 0).firstCursorPosition().insertText("Mortalities");
    table->cellAt(4, 0).firstCursorPosition().insertText("Recaptures");


    int row = 1;
    printDataInfoRow(table, row++, runItem.datadir, runItem.obs);
    printDataInfoRow(table, row++, runItem.datadir, runItem.tag);
    printDataInfoRow(table, row++, runItem.datadir, runItem.mort);
    printDataInfoRow(table, row++, runItem.datadir, runItem.recap);

    cursor.endEditBlock();
    cursor.movePosition(QTextCursor::End);
}

void ResultsManagerImpl::printDataInfoRow(QTextTable* table, int row, const QString& dir, const QString& fileName) {
    QString filePath = dir + "/" + fileName;
    QFileInfo fi(filePath);
//    stringstream ss;
    if (fi.exists()) {
        table->cellAt(row, 1).firstCursorPosition().insertHtml("<a href=\"" + fileName + "\">" + fileName + "</a>");
        table->cellAt(row, 2).firstCursorPosition().insertText(QString::number(fi.size()), tableDataFormat);
        table->cellAt(row, 3).firstCursorPosition().insertText(fi.lastModified().toString());
    } else {
        table->cellAt(row, 1).firstCursorPosition().insertText("NA");
        table->cellAt(row, 2).firstCursorPosition().insertText("NA");
        table->cellAt(row, 3).firstCursorPosition().insertText("NA");
    }

}

void ResultsManagerImpl::writeFileInfoRow(QTextTable* table, int row, const QFileInfo& fi) {
//    stringstream ss;
    QString fileName = fi.fileName();
    PitProSettings& settings = PitProSettings::getInstance();
    QString outputDir = settings.getValue(PitProSettings::OutputDir);
    QString filePath = outputDir + "/" + fileName;

    table->cellAt(row, 0).firstCursorPosition().insertHtml("<a href=\"" + fileName + "\">" + fileName + "</a>");
    table->cellAt(row, 1).firstCursorPosition().insertText(QString::number(fi.size()));
    table->cellAt(row, 2).firstCursorPosition().insertText(fi.lastModified().toString());
}

void ResultsManagerImpl::getOutputByPrefix(QTextCursor& cursor, const QString& prefix, bool combined) {
    PitProSettings& settings = PitProSettings::getInstance();
    QString outputDir = settings.getValue(PitProSettings::OutputDir);
    QDir dir(outputDir);
    dir.refresh();

    QString filter;
    filter += prefix + "." + settings.getValue(PitProSettings::ErrorSuffix);
    filter += ";" + prefix + "." + settings.getValue(PitProSettings::TtSuffix);
    filter += ";" + prefix + "." + settings.getValue(PitProSettings::DdSuffix);
    filter += ";" + prefix + "." + settings.getValue(PitProSettings::SeqSuffix);
    if (!combined)
        filter += ";" + prefix + "." + settings.getValue(PitProSettings::SurphSuffix);

    QStringList filters(filter);
    dir.setNameFilters(filters);

    QStringList entryList = dir.entryList(filters);//dir.entryList(filter.c_str());
    stringstream ss;

    if (entryList.size() == 0) {
        cursor.insertBlock(paragraphTbf);
        cursor.insertText("No data found.", boldText);
    } else {
        // make the summary report (in html format)
        cursor.insertBlock(sectionTbf);
        cursor.insertText("Output files for \"" + prefix + "\":", heading3);

        cursor.insertBlock(paragraphTbf);
        QTextTable* table = cursor.insertTable(entryList.size() + 1, 3, tableFormat);
        setRowHeaderFormats(table, 0);
        writeFileInfoHeader(table);

        // to do
        int row = 1;
        for (QStringList::iterator it = entryList.begin(); it != entryList.end(); ++it) {
            const QString& file = *it;
            QFileInfo fi(dir, file);
            writeFileInfoRow(table, row++, fi);
        }
        cursor.movePosition(QTextCursor::End);
    }
}

void ResultsManagerImpl::getCombinedSummaryOutput(QTextCursor& cursor, const QString& prefix) {
//    stringstream ss;

    PitProSettings& settings = PitProSettings::getInstance();
    QString suffix = settings.getValue(PitProSettings::SurphSuffix);

    QString outputDir = settings.getValue(PitProSettings::OutputDir);
    QString chFile = outputDir + "/" + prefix + "." + suffix;
    QFileInfo fi(chFile);
    if (fi.exists()) {
        // make the summary report (in html format)
        cursor.insertBlock(paragraphTbf);
        cursor.insertText("Capture History file for combined group \"" + prefix + "\":", boldText);
        cursor.insertBlock(paragraphTbf);
        QTextTable* table = cursor.insertTable(2, 3, tableFormat);
        setRowHeaderFormats(table, 0);
        writeFileInfoHeader(table);
        writeFileInfoRow(table, 1, fi);
        cursor.movePosition(QTextCursor::End);
    }
}

void ResultsManagerImpl::writeFileInfoHeader(QTextTable* table) {
    table->cellAt(0, 0).firstCursorPosition().insertText("Name", tableHeaderFormat);
    table->cellAt(0, 1).firstCursorPosition().insertText("Size (bytes)", tableHeaderFormat);
    table->cellAt(0, 2).firstCursorPosition().insertText("Last Modified Date", tableHeaderFormat);
}

void ResultsManagerImpl::createCjsReport(QTextCursor& cursor, const surph::SurphData& surphData, QList<CjsEstimates *> &estimates, const QString &prefix) {
    PPRunInfo& runInfo = PPRunInfo::instance();
    if (!runInfo.load(prefix)) {
        cursor.insertBlock(paragraphTbf);
        cursor.insertText("Can't find run info.", boldText);
    } else {
        PPSystemSettings &systemSettings = PPSystemSettings::getInstance();
        const int estp = systemSettings.get(PPSystemSettings::EstPrecision).toInt();
        const int errp = systemSettings.get(PPSystemSettings::ErrPrecision).toInt();

        cursor.insertText("Cormack/Jolly-Seber Estimates for \"" + prefix + "\"", heading1);
        cursor.insertBlock(linebreakTbf);
        cursor.insertText("(Cormack 1964, Jolly 1965, Seber 1965)", bodyText);

        cursor.insertBlock(paragraphTbf);

        cursor.insertText("Note: This report is only valid for juvenile life cycle data. Survival estimates "
                "to adult migration sites are not valid.", bodyText);

        cursor.insertBlock(paragraphTbf);
        cursor.insertText("Data: ", boldText);
        cursor.insertText(surphData.dataDescription(), bodyText);
        cursor.insertBlock(linebreakTbf);
        cursor.insertText("File: ", boldText);
        cursor.insertText(surphData.fileName(), bodyText);

        cursor.movePosition(QTextCursor::End);

        cursor.insertBlock(sectionTbf);

        bool oneTable = oneTableCjsCB->isChecked();

        if (oneTable)
            cursor.insertText("Parameter Estimates", heading2);
        else
            cursor.insertText("Survival Probabilities", heading2);
        cursor.insertBlock(paragraphTbf);

        bool showLambda = showLambdaCB->isChecked();
        int numCols;
        int numRows;
        int headerRows;
        const int numPeriods = surphData.numPeriods();
        if (oneTable) {
            headerRows = 2;
            numRows = surphData.numPopulations() + 2;
            numCols = (numPeriods * 2) + (showLambda ? 1 : 0);
        } else {
            headerRows = 1;
            numRows = surphData.numPopulations() + 1;
            numCols = numPeriods + 1;
        }

        QTextTable* table = cursor.insertTable(numRows, numCols, tableFormat);

        setTableHeaderFormats(table, headerRows);

        int col = 0;
        table->cellAt(headerRows - 1, col++).firstCursorPosition().insertText("Population");
        if (oneTable)
            table->cellAt(headerRows - 1, numCols - 1).firstCursorPosition().insertText("Final Product");

        int i;

        int numMainSites = runInfo.getNumMainSites();
        bool isSiteRel = runInfo.isSiteRel();
        if (numMainSites == numPeriods)
            isSiteRel = true; // cover up bug of not recording isSiteRel in old config files

        if (oneTable) {
            table->mergeCells(0, 1, 1, numPeriods);
            table->cellAt(0, 1).firstCursorPosition().insertText("Survival");
            table->mergeCells(0, numPeriods + 1, 1, numMainSites);
            table->cellAt(0, numPeriods + 1).firstCursorPosition().insertText("Capture Probability");
            table->mergeCells(0, 0, 2, 1);
            table->mergeCells(0, numCols - 1, 2, 1);
        }

        Sites *sites = Sites::getInstance();
        QStringList allSites = runInfo.getAllSites();
        QStringList::const_iterator it = allSites.begin();
        QString releaseSite("Rel");
        int field = 0;
        if (isSiteRel && it != allSites.end()) {
            const Site *site = sites->getSite(*it);
            releaseSite = site->getShortName();
            field = 1;
            ++it;
        }
        QString prevSite(releaseSite);

        for (; it != allSites.end(); ++it) {
            const Site *site = sites->getSite(*it);
            if (field < numMainSites) {
                QString currSite = site->getShortName();
                QString label = prevSite + "-" + currSite;
                table->cellAt(headerRows - 1, col++).firstCursorPosition().insertText(label);
                prevSite = currSite;
                ++field;
            }
        }
        QString lastSite = prevSite;

        QString overallReach = releaseSite + "-" + lastSite;
        table->cellAt(headerRows - 1, col++).firstCursorPosition().insertText(overallReach);

        for (int j = 0; j < surphData.numPopulations(); ++j) {
            col = 0;
            table->cellAt(headerRows + j, col++).firstCursorPosition().insertText(QString(surphData.populationName(j)), tableHeaderFormat);

            for (i = 1; i < surphData.numPeriods(); ++i) {
                int phiIndex = estimates[j]->phiIndex(i);
                double est = estimates[j]->phi(i);
                double se = sqrt(estimates[j]->covariance()(phiIndex, phiIndex));
                QString s = QString::number(est, 'f', estp) + " (" + QString::number(se, 'f', errp) + ")";

                table->cellAt(headerRows + j, col++).firstCursorPosition().insertText(s, tableDataFormat);
            }

            double est = estimates[j]->phi(1);
            for (int k = 2; k < surphData.numPeriods(); ++k)
                est *= estimates[j]->phi(k);
            double se = sqrt(estimates[j]->reachVariance(1, surphData.numPeriods() - 1));
            QString s = QString::number(est, 'f', estp) + " (" + QString::number(se, 'f', errp) + ")";
            table->cellAt(headerRows + j, col++).firstCursorPosition().insertText(s, tableDataFormat);
        }

        int startCol;
        if (oneTable)
            startCol = col - 1;
        else {
            cursor.movePosition(QTextCursor::End);

            cursor.insertBlock(sectionTbf);
            cursor.insertText("Capture Probabilities", heading2);
            cursor.insertBlock(paragraphTbf);

            table = cursor.insertTable(surphData.numPopulations() + 1, surphData.numPeriods(), tableFormat);
            setTableHeaderFormats(table, headerRows);

            table->cellAt(0, 0).firstCursorPosition().insertText("Population");

            startCol = 0;
        }

        it = allSites.begin();
        field = 0;
        if (isSiteRel && it != allSites.end()) {
            ++it;
            field = 1;
        }
        int col2 = 0;
        for (; it != allSites.end(); ++it) {
            if (field < numMainSites) {
                const Site *site = sites->getSite(*it);
                QString currSite = site->getShortName();
                table->cellAt(headerRows - 1, startCol + col2++ +1).firstCursorPosition().insertText(currSite);
                ++field;
            }
        }

        for (int j = 0; j < surphData.numPopulations(); ++j) {
            if (!oneTable)
                table->cellAt(j + 1, 0).firstCursorPosition().insertText(QString(surphData.populationName(j)), tableHeaderFormat);

            int i;
            for (i = 2; i <= surphData.numPeriods(); ++i) {
                const int pIndex = estimates[j]->pIndex(i);
                double est = estimates[j]->p(i);
                double se = sqrt(estimates[j]->covariance()(pIndex, pIndex));

                QString s = QString::number(est, 'f', estp) + " (" + QString::number(se, 'f', errp) + ")";
                table->cellAt(headerRows + j, startCol + i - 1).firstCursorPosition().insertText(s, tableDataFormat);
            }
        }

        if (!oneTable)
            cursor.movePosition(QTextCursor::End);

        if (showLambda) {
            int lambdaCol;
            if (oneTable)
                lambdaCol = table->columns() - 1;
            else {
                lambdaCol = 1;
                cursor.insertBlock(sectionTbf);
                cursor.insertText("Final Product (lambda)", heading2);
                cursor.insertBlock(paragraphTbf);

                table = cursor.insertTable(surphData.numPopulations() + 1, 2, tableFormat);
                setTableHeaderFormats(table, headerRows);
            }
            if (!oneTable) {
                table->cellAt(0, 0).firstCursorPosition().insertText("Population");
                table->cellAt(0, lambdaCol).firstCursorPosition().insertText("Final Product");
            }

            for (int j = 0; j < surphData.numPopulations(); ++j) {
                if (!oneTable)
                    table->cellAt(j + 1, 0).firstCursorPosition().insertText(QString(surphData.populationName(j)), tableHeaderFormat);

                int phiIndex = estimates[j]->phiIndex(surphData.numPeriods());
                double est = estimates[j]->phi(surphData.numPeriods());
                double se = sqrt(estimates[j]->covariance()(phiIndex, phiIndex));
                QString s = QString::number(est, 'f', estp) + " (" + QString::number(se, 'f', errp) + ")";
                table->cellAt(headerRows + j, lambdaCol).firstCursorPosition().insertText(s, tableDataFormat);
            }

            if (!oneTable)
                cursor.movePosition(QTextCursor::End);
        }

        if (oneTable)
            cursor.movePosition(QTextCursor::End);

        //insertCjsKey(cursor, surphData, prefix, showLambda);
    }
}

void ResultsManagerImpl::insertCjsKey(QTextCursor& cursor, const surph::SurphData& surphData, const QString &prefix, bool showLambda) {
    PPRunInfo& runInfo = PPRunInfo::instance();
    if (runInfo.load(prefix)) {
        listFormat.setStyle(QTextListFormat::ListDisc);
        QStringList juvSites = runInfo.getJuvenileSites();
        int numJuvSites = juvSites.size();
        int numMainSites = runInfo.getNumMainSites();

        int numPeriods = surphData.numPeriods();
        bool siteRel = PitProSettings::getInstance().isChecked(PitProSettings::SiteRel);

        QTextBlockFormat keyBlockFormat = sectionTbf;
        keyBlockFormat.setTopMargin(2 * sectionTbf.topMargin());
        cursor.insertBlock(keyBlockFormat);
        cursor.insertText("Key", heading2);
        cursor.insertBlock(paragraphTbf);

        int numRows = (numPeriods * 2) - 1 + (showLambda ? 1 : 0);
        QTextTableFormat keyTff;
        keyTff.setLeftMargin(10);
        keyTff.setBorder(0);
        QTextTable* table = cursor.insertTable(numRows, 2, keyTff);

        int row = 0;
        int i;
        int field = (siteRel) ? 1 : 0;
        for (i = 1; i < surphData.numPeriods(); ++i) {
            QString reach1 = (field == 0) ? "release" : juvSites[field - 1];

            table->cellAt(row, 0).firstCursorPosition().insertText("S" + QString::number(i) + ": ");
            QTextCursor cellCursor = table->cellAt(row++, 1).firstCursorPosition();
            cellCursor.insertText("Survival from ", bodyText);
            cellCursor.insertText(reach1, bodyText);
            cellCursor.insertText(" to ", bodyText);
            cellCursor.insertText(juvSites[field], bodyText);
            cellCursor.insertText(".", bodyText);
            field++;
        }

        for (i = 1; i < surphData.numPeriods(); ++i) {
            table->cellAt(row, 0).firstCursorPosition().insertText("P" + QString::number(i) + ": ");
            QTextCursor cellCursor = table->cellAt(row++, 1).firstCursorPosition();
            cellCursor.insertText("Capture probability at ", bodyText);
            cellCursor.insertText(juvSites[i - 1], bodyText);
            cellCursor.insertText(".", bodyText);
        }

        if (showLambdaCB->isChecked()) {
            table->cellAt(row, 0).firstCursorPosition().insertText("Final Product: ");
            QTextCursor cellCursor = table->cellAt(row++, 1).firstCursorPosition();
            if (numMainSites == numJuvSites) {
                QString lastField = juvSites[numMainSites - 1];
                cellCursor.insertText("The probability of surviving to and being detected at ", bodyText);
                cellCursor.insertText(lastField, bodyText);
            }
            else {
                QString lastField = juvSites[numMainSites];
                cellCursor.insertText("The probability of surviving to ", bodyText);
                cellCursor.insertText(lastField, bodyText);
                cellCursor.insertText(" and being detected at ", bodyText);
                for (int i = numMainSites; i < numJuvSites; ++i) {
                    cellCursor.insertText(juvSites[i]);
                    if (i == numJuvSites - 2)
                        cellCursor.insertText(" or ", bodyText);
                    else if (i < numJuvSites - 1)
                        cellCursor.insertText(", ", bodyText);
                }
            }
            cellCursor.insertText(". This value is necessary for computational purposes and isn't generally reported on its own.", bodyText);
        }

        QString reach1;
        QString reach2;
        if (siteRel) {
            reach1 = juvSites[0];
            reach2 = juvSites[numMainSites - 2];
        } else {
            reach1 = "release";
            reach2 = juvSites[numMainSites - 1];
        }
        table->cellAt(row, 0).firstCursorPosition().insertText("Overall S: ");
        QTextCursor cellCursor = table->cellAt(row++, 1).firstCursorPosition();
        cellCursor.insertText("Overall survival from ", bodyText);
        cellCursor.insertText(reach1, bodyText);
        cellCursor.insertText(" to ", bodyText);
        cellCursor.insertText(reach2, bodyText);
        cellCursor.insertText(".", bodyText);

        cursor.movePosition(QTextCursor::End);
    }
}

QString ResultsManagerImpl::getStageKey(int& numJuvSites) const {
    stringstream ss;
    if (numJuvSites == 0)
        ss << " (A)";
    else if (numJuvSites > 0) {
        --numJuvSites;
        ss << " (J)";
    }

    return QString(ss.str().c_str());
}

void ResultsManagerImpl::createCjsDataReport(QTextCursor& cursor, const surph::SurphData& surphData, QList<CjsEstimates*>& estimates, const QString& /*prefix*/) {
    const int estp = 12;
    const int errp = 12;

    QString sstr("population");
//    stringstream ss;

//    ss << "population";
    for (int i = 1; i < surphData.numPeriods(); ++i) {
        sstr.append(QString(",s%1,s%1_se").arg(QString::number(i)));//toString<int>(i)));
//        ss << "," << "s" << toString<int>(i);
//        ss << "," << "s" << toString<int>(i) << "_se";
    }
    for (int i = 1; i < surphData.numPeriods(); ++i) {
        sstr.append(QString(",p%1,p%1_se").arg(QString::number(i)));//toString<int>(i)));
//        ss << "," << "p" << toString<int>(i);
//        ss << "," << "p" << toString<int>(i) << "_se";
    }
    sstr.append(QString(",final_product,final_product_se"));
    sstr.append(QString(",overall_s,overall_s_se\n"));
//    ss << ",final_product,final_product_se";
//    ss << ",overall_s,overall_s_se\n";

    for (int j = 0; j < surphData.numPopulations(); ++j) {
        sstr.append(surphData.populationName(j));
//        ss << surphData.populationName(j);

        int i;
        for (i = 1; i < surphData.numPeriods(); ++i) {
            int phiIndex = estimates[j]->phiIndex(i);
            double est = estimates[j]->phi(i);
            double var = estimates[j]->covariance()(phiIndex, phiIndex);

            sstr.append(QString(",%1").arg(formatEstimate(est, estp)));
            sstr.append(QString(",%1").arg(formatSe(var, errp)));
//            ss << "," << formatEstimate(est, estp).toStdString();
//            ss << "," << formatSe(var, errp).toStdString();
        }

        double productEst = estimates[j]->phi(1);
        for (int k = 2; k < surphData.numPeriods(); ++k)
            productEst *= estimates[j]->phi(k);
        double productVar = estimates[j]->reachVariance(1, surphData.numPeriods() - 1);

        for (i = 2; i <= surphData.numPeriods(); ++i) {
            const int pIndex = estimates[j]->pIndex(i);
            double est = estimates[j]->p(i);
            double var = estimates[j]->covariance()(pIndex, pIndex);

            sstr.append(QString(",%1").arg(formatEstimate(est, estp)));
            sstr.append(QString(",%1").arg(formatSe(var, errp)));
//            ss << "," << formatEstimate(est, estp).toStdString();
//            ss << "," << formatSe(var, errp).toStdString();
        }

        int phiIndex = estimates[j]->phiIndex(surphData.numPeriods());
        double est = estimates[j]->phi(surphData.numPeriods());
        double var = estimates[j]->covariance()(phiIndex, phiIndex);

        sstr.append(QString(",%1").arg(formatEstimate(est, estp)));
        sstr.append(QString(",%1").arg(formatSe(var, errp)));
//        ss << "," << formatEstimate(est, estp).toStdString();
//        ss << "," << formatSe(var, errp).toStdString();

        sstr.append(QString(",%1").arg(formatEstimate(productEst, estp)));
        sstr.append(QString(",%1\n").arg(formatSe(productVar, errp)));
//        ss << "," << formatEstimate(productEst, estp).toStdString();
//        ss << "," << formatSe(productVar, errp).toStdString();

//        ss << "\n";
    }
    cursor.insertText(sstr, bodyText);
//    cursor.insertText(ss.str().c_str(), bodyText);
}

void ResultsManagerImpl::createCovarianceReport(QTextCursor& cursor, const surph::SurphData& surphData, const QString &prefix) {
    QString sstr;
    sstr.append(QString("Covariance Matrix Report for \"%1\"\n\n").arg(prefix));
//    stringstream ss;
//    ss << "Covariance Matrix Report for \"" << prefix << "\"" << std::endl << std::endl;

    int numPop = surphData.numPopulations();
    QList<CjsStatistics*> statistics;//(numPop);
    for (int i = 0; i < numPop; ++i)
        statistics.append(new CjsStatistics(surphData.captureHistoryMap(i), surphData.numPeriods()));
//        statistics[i] = new CjsStatistics(surphData.captureHistoryMap(i), surphData.numPeriods());

    // CJS estimates
    for (int i = 0; i < numPop; ++i) {
        CjsEstimates* estimates = new CjsEstimates(*statistics[i]);
        QString popName = surphData.populationName(i);

        if (numPop > 1)
            sstr.append(QString("Covariance Matrix for population \"%1\"\n\n").arg(popName));
//            ss << "Covariance Matrix for population \"" << popName << "\"" << std::endl << std::endl;

        Matrix<double> covarMatrix = estimates->covariance();
//        ss.precision(8);
        for (int j = 0; j < covarMatrix.rows(); j++) {
            for (int i = 0; i < covarMatrix.cols(); ++i) {
                double val = covarMatrix(i, j);

                if (i > 0)
                    sstr.append(",");
//                    ss << ",";
                if (val != val)
                    sstr.append("NAN");
//                    ss << "NAN";
                else
                    sstr.append(QString::number(val, 'g', 8));
//                    ss << std::fixed << val;
            }
            sstr.append('\n');
//            ss << std::endl;
        }
        sstr.append('\n');
//        ss << std::endl;



        delete estimates;
    }
    while (statistics.count() > 0)
        delete statistics.takeLast();

    QString covarReport(sstr);
    cursor.insertText(covarReport);
}

void ResultsManagerImpl::doCjsData() {
    updateCjsPage(); // update covar report if necessary
    QString output = cjsDataTextEdit.toPlainText();

    const QString& group = groupCombo->currentText();
    QString fileName = group + "_cjs_data.csv";
    saveFile(fileName, output, "CSV (*.csv)");
}

void ResultsManagerImpl::doCovarianceMatrix() {
    updateCjsPage(); // update covar report if necessary);
    QString output = covarTextEdit.toPlainText();

    const QString& group = groupCombo->currentText();
    QString fileName = group + "_covar.txt";
    saveFile(fileName, output, "Text (*.txt)");
}

void ResultsManagerImpl::doTTData() {
    updateTtPage(QString::null); // update tt report if necessary
    QString output = ttDataTextEdit.toPlainText();

    const QString& group = groupCombo->currentText();
    QString fileName = group + "_tt_data.csv";
    saveFile(fileName, output, "CSV (*.csv)");
}

void ResultsManagerImpl::createErrorReport(QTextCursor& cursor, const QString& prefix) {
    // write report

    cursor.beginEditBlock();
    cursor.insertText("Error Report for \"" + prefix + "\"", heading1);

    // get the error file name
    PitProSettings& settings = PitProSettings::getInstance();
    QString errorFileName = prefix + "." + settings.getValue(PitProSettings::ErrorSuffix);
    QString errorFilePath = settings.getOutFilePath(errorFileName);

    ifstream in(errorFilePath.toStdString().data());
    if (!in.is_open()) {
        cursor.insertBlock(paragraphTbf);
        cursor.insertText("No error results found.", boldText);
    } else { // file opened successfully
        string line;
        int numRemoved = 0;
        vector<int> errorCounts(PPErrors::NumErrorTypes, 0);
        while (getline(in, line)) {
            stringstream instream(line);
            PPErrors errors;
            instream >> errors;
            if (errors.isValid()) {
                ++numRemoved;
                for (unsigned i = 0; i < PPErrors::NumErrorTypes; ++i) {
                    PPErrors::ErrorType type = static_cast<PPErrors::ErrorType> (i);
                    errorCounts[i] += (errors.isSet(type) ? 1 : 0);
                }
            }
        }
        in.close();

        // make report
        cursor.insertBlock(sectionTbf);
        cursor.insertText("Error Summary", heading2);
        cursor.insertBlock(linebreakTbf);
        cursor.insertText("Note: the first column in the error file is the tag id. So the first"
                " error is the second column in the error file.", italicText);

        cursor.insertBlock(sectionTbf);
        QTextTable* table = cursor.insertTable(errorCounts.size() + 2, 3, tableFormat);
        setRowHeaderFormats(table, 0);
        table->cellAt(0, 0).firstCursorPosition().insertText("Error");
        table->cellAt(0, 1).firstCursorPosition().insertText("Description");
        table->cellAt(0, 2).firstCursorPosition().insertText("Count");

        unsigned int i;
        int row = 1;
        for (i = 0; i < errorCounts.size(); ++i) {
            QString errorText = PPErrors::getText(static_cast<PPErrors::ErrorType> (i));

            table->cellAt(row, 0).firstCursorPosition().insertText(QString::number(row), tableDataFormat);
            table->cellAt(row, 1).firstCursorPosition().insertText(errorText, tableDataFormat);
            table->cellAt(row, 2).firstCursorPosition().insertText(QString::number(errorCounts[i]), tableDataFormat);

            row++;
        }

        table->cellAt(row, 1).firstCursorPosition().insertText("Total", boldText);
        table->cellAt(row, 2).firstCursorPosition().insertText(QString::number(numRemoved), tableDataFormat);
    }

    cursor.endEditBlock();
}

void ResultsManagerImpl::createTTTableReport(QTextCursor& cursor, const QStringList& headers, const cbr::Matrix<cbr::DoubleVector>& ttMatrix, const QString& prefix) {
    // write report
    cursor.insertText("Travel Time Estimates (days) for \"" + prefix + "\"", heading1);

    cursor.beginEditBlock();
    cursor.insertBlock(sectionTbf);
    cursor.insertText("Arithmetic means (with Standard Errors):", heading2);
    cursor.insertBlock(paragraphTbf);
    getResultsTable(cursor, headers, ttMatrix, AMEAN);
    cursor.movePosition(QTextCursor::End);
    cursor.endEditBlock();
    qApp->processEvents();

    cursor.beginEditBlock();
    cursor.insertBlock(sectionTbf);
    cursor.insertText("Harmonic means (with Standard Errors):", heading2);
    cursor.insertBlock(paragraphTbf);
    getResultsTable(cursor, headers, ttMatrix, HMEAN);
    cursor.movePosition(QTextCursor::End);
    cursor.endEditBlock();
    qApp->processEvents();

    cursor.beginEditBlock();
    cursor.insertBlock(sectionTbf);
    cursor.insertText("Counts:", heading2);
    cursor.insertBlock(paragraphTbf);
    getResultsTable(cursor, headers, ttMatrix, COUNT);
    cursor.movePosition(QTextCursor::End);
    cursor.endEditBlock();
    qApp->processEvents();
}

void ResultsManagerImpl::createTTDataReport(QTextCursor& cursor, const QStringList &headers,
        const cbr::Matrix<cbr::DoubleVector>& ttMatrix, const QString& /*prefix*/) {
    QString sstr;
//    stringstream ss;

    const int dp = 15;

    sstr.append("site 1, site 2, arithmetic mean, arithmetic mean se, harmonic mean, harmonic mean se, count\n");
//    ss << "site 1, site 2, arithmetic mean, arithmetic mean se, harmonic mean, harmonic mean se, count\n";

    for (int i = 0; i < ttMatrix.rows() - 1; i++) {
        for (int j = 1; j < ttMatrix.cols(); j++) {
            if (j > i) {
                sstr.append(QString("%1,%2").arg(headers.at(i), headers.at(j)));
//                ss << headers[i] << "," << headers[j];

                const DoubleVector& tts = ttMatrix(i, j);

//                ss << std::fixed;
//                ss.precision(dp);

                // mean
                sstr.append(",");
//                ss << ",";
                if (tts.size() == 0) {
                    sstr.append("NA,NA");
//                    ss << "NA,NA";
                }
                else {
                    double mean = Statistics::amean(tts);
                    double se = sqrt(Statistics::var(tts));

                    sstr.append(QString("%1,%2").arg(QString::number(mean, 'g', dp),
                                                     QString::number(se, 'g', dp)));
//                    ss << mean << "," << se;
                }

                // hmean
                sstr.append(",");
//                ss << ",";
                if (tts.size() == 0) {
                    sstr.append("NA,NA");
//                    ss << "NA,NA";
                }
                else {
                    double mean = Statistics::hmean(tts);
                    double se = sqrt(Statistics::hvar(tts));
                    sstr.append(QString("%1,%2").arg(QString::number(mean, 'g', dp),
                                                     QString::number(se, 'g', dp)));
//                    ss << mean << "," << se;
                }

                // count
                sstr.append(QString(",%1\n").arg(QString::number(tts.size())));
//                ss << "," << tts.size();

//                ss << "\n";
            }
        }
    }
    cursor.insertText(sstr, bodyText);
//    cursor.insertText(ss.str().c_str(), bodyText);
}

void ResultsManagerImpl::getResultsTable(QTextCursor& cursor, const QStringList &headers,
        const Matrix<DoubleVector>& ttMatrix,
        ResultsType type) {
    // formats
    //int width = (int)( 100.0 / ( headers.size() + 1 ) );
    //tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    QTextTableFormat ttTableFormat = tableFormat;
    ttTableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 95));

    QTextTable* table = cursor.insertTable(ttMatrix.rows(), ttMatrix.cols(), ttTableFormat);
    for (int i = 0; i < table->columns(); ++i)
        table->cellAt(0, i).setFormat(tableHeaderFormat);
    for (int j = 1; j < table->rows(); ++j)
        table->cellAt(j, 0).setFormat(tableHeaderFormat);

    QStringList::const_iterator it = headers.begin();
    ++it;
    int col = 1;
    for (; it != headers.end(); it++) {
        table->cellAt(0, col++).firstCursorPosition().insertText(QString((*it)));
    }

    for (int i = 0; i < ttMatrix.rows() - 1; i++) {
        table->cellAt(i + 1, 0).firstCursorPosition().insertText(QString(headers[i]));

        for (int j = 1; j < ttMatrix.cols(); j++) {
            if (j <= i) {
                table->cellAt(i + 1, j).firstCursorPosition().setBlockFormat(centerTbf);
                table->cellAt(i + 1, j).firstCursorPosition().insertText("--");
            } else {
                const DoubleVector& tts = ttMatrix(i, j);

                stringstream ss;
                ss << std::fixed;
                ss.precision(p);
                switch (type) {
                    case AMEAN:
                        if (tts.size() == 0)
                            ss << "NA";
                        else {
                            double mean = Statistics::amean(tts);
                            double se = sqrt(Statistics::var(tts));

                            ss << mean << " (" << se << ")";
                        }
                        break;
                    case ASE:
                        if (tts.size() == 0)
                            ss << "NA";
                        else {
                            double se = sqrt(Statistics::var(tts));
                            ss << se;
                        }
                        break;
                    case HMEAN:
                        if (tts.size() == 0)
                            ss << "NA";
                        else {
                            double mean = Statistics::hmean(tts);
                            double se = sqrt(Statistics::hvar(tts));
                            ss << mean << " (" << se << ")";
                        }
                        break;
                    case HSE:
                        if (tts.size() == 0)
                            ss << "NA";
                        else {
                            double se = sqrt(Statistics::hvar(tts));
                            ss << se;
                        }
                        break;
                    case COUNT:
                        ss << tts.size();
                        break;
                }

                table->cellAt(i + 1, j).firstCursorPosition().setBlockFormat(rightTbf);
                table->cellAt(i + 1, j).firstCursorPosition().insertText(QString(ss.str().c_str()));
            }
        }
    }
}

/*****************************
 * PIT Tracker report methods
 ****************************/

void ResultsManagerImpl::trackPitCode() {
    QString currentPitcode = pitComboBox->currentText().simplified();
    const QString pitCode(currentPitcode);
    if (!PPData::isValidPitTag(currentPitcode)) {
        QMessageBox::critical(this, "PitPro", "Input is not a valid PIT-Tag");
        return;
    }

    if (pitComboBox->findText(currentPitcode) == -1) {
        pitComboBox->insertItem(-1, currentPitcode);
        pitComboBox->setCurrentIndex(0);
    }

    statusBar()->showMessage("Tracking PIT code \"" + currentPitcode + "\"...");

    QTextCursor cursor = clearFrame(trackerTextEdit);

    PPRunInfo& runInfo = PPRunInfo::instance();
    const QString& prefix = groupCombo->currentText();
    QString filePath = runInfo.getConfigFileName(prefix);
    if (prefix.isEmpty())
        cursor.insertText("No group selected.", boldText);
    else if (!runInfo.load(prefix))
        cursor.insertText("Can't find run configuration information.", boldText);
    else {
        QString outputDir = runInfo.getOutputDir();
        QString dataDir = runInfo.getDataDir();

        cursor.beginEditBlock();
        cursor.insertText("Summary Report for " + pitCode, heading1);
        getOneFishSummary(cursor, runInfo, prefix, pitCode);
        cursor.endEditBlock();

        if (trackerDetailCheckBox->isChecked()) {
            cursor.beginEditBlock();
            cursor.insertBlock(sectionTbf);
            cursor.insertText("Output for " + pitCode, heading1);
            getOneFishOutput(cursor, runInfo, prefix, pitCode);
            cursor.endEditBlock();

            cursor.beginEditBlock();
            cursor.insertBlock(sectionTbf);
            cursor.insertText("Raw Data for " + pitCode, heading1);
            getOneFishData(cursor, runInfo, pitCode);
            cursor.endEditBlock();
        }
    }

    statusBar()->showMessage("done.", 5000);
}

void ResultsManagerImpl::getOneFishSummary(QTextCursor& cursor, const PPRunInfo& runInfo, const QString &prefix, const QString &target) {
    stringstream ss;

    // Data summary
    cursor.insertBlock(paragraphTbf);
    cursor.insertText("Results Summary:", heading2);
    getOneFishOutputSummary(cursor, runInfo, prefix, target);
    qApp->processEvents();

    cursor.insertBlock(paragraphTbf);
    cursor.insertText("Interrogation Data Summary View:", heading2);
    getOneFishDataSummary(cursor, runInfo, target);
    qApp->processEvents();
}

void ResultsManagerImpl::getOneFishOutputSummary(QTextCursor& cursor, const PPRunInfo& runInfo, const QString &prefix, const QString &target) {
    PitProSettings& settings = PitProSettings::getInstance();
    const QString& outputDir = runInfo.getOutputDir();

    QString sstr;
//    stringstream ss;
    int resultRows = 0;

    const QString& surphSuff = settings.getValue(PitProSettings::SurphSuffix);
    QStringList v = getMatchingRows(outputDir, prefix + "." + surphSuff, target);
    if (v.size() != 0) {
        resultRows += v.size();

        bool first = true;
        QTextTable* table = 0;
        for (QStringList::const_iterator it = v.begin(); it != v.end(); ++it) {
            const QString& line = *it;
            QStringList toks;
//            StringVector toks;
            stringTok(toks, line);

            if (first) {
                first = false;
                int col = 0;
                table = cursor.insertTable(2, toks.size(), tableFormat);
                setRowHeaderFormats(table, 0);

                table->cellAt(0, col++).firstCursorPosition().insertText("Tag ID", tableHeaderFormat);

                QString outputFormat = runInfo.getOutputFormat();
                if (outputFormat.compare("ROSTER") != 0)
                    table->cellAt(0, col++).firstCursorPosition().insertText("rel", tableHeaderFormat);

                int numMainSites = runInfo.getNumMainSites();
                int field = 0;
                QStringList juvenSites = runInfo.getJuvenileSites();
                int numJuvenileSites = juvenSites.size();//allSites.size();
                QStringList adultSites = runInfo.getAdultSites();
                QStringList allSites(adultSites);
                allSites.append(juvenSites);
//                allSites.insert(allSites.end(), adultSites.begin(), adultSites.end());
                if (settings.isChecked(PitProSettings::SiteRel)) {
                    ++field;
                    allSites.erase(allSites.begin());
                }

                QString sstr;
//                stringstream ss;
                for (QStringList::const_iterator it2 = allSites.begin(); it2 != allSites.end(); ++it2) {
                    ++field;

                    if (field <= numMainSites + 1) {
                        sstr.append(*it2);
//                        ss.str("");
//                        ss << *it2;
                    } else
                        sstr.append("+" + *it2);
//                        ss << "+" << *it2;

                    if (field > numJuvenileSites)
                        sstr.append("a");
//                        ss << "a";

                    if (field < numMainSites + 1)
                        table->cellAt(0, col++).firstCursorPosition().insertText(sstr, tableHeaderFormat);

                }
                if (field > numMainSites)
                    table->cellAt(0, col++).firstCursorPosition().insertText(sstr, tableHeaderFormat);

                // make headers for icovs
                if (outputFormat.compare("ROSTER") != 0) {
                    int icov = 1;
                    while (field++ < toks.size() - 2)
                        table->cellAt(0, col++).firstCursorPosition().insertText("icov " + QString::number(icov++), tableHeaderFormat);
                }
            }

            int col = 0;
            for (col = 0; col < toks.count(); col++)
            {
                table->cellAt(1, col).firstCursorPosition().insertText(toks.at(col), tableDataFormat);
            }
// TODO: Fix
/*            for (StringVector::const_iterator it3 = toks.begin(); it3 != toks.end(); ++it3) {
                table->cellAt(1, col++).firstCursorPosition().insertText(QString((*it3).c_str()), tableDataFormat);
            }*/
        }
    } else {
        QStringList runNames = runInfo.getRunNames();
        const QString& errorSuff = settings.getValue(PitProSettings::ErrorSuffix);

        for (QStringList::iterator it = runNames.begin(); it != runNames.end(); ++it) {
            const QString& runName = *it;
            QString errorFile = runName + "." + errorSuff;
            v = getMatchingRows(outputDir, errorFile, target);
            if (v.size() > 0) {
                resultRows += v.size();

                cursor.insertBlock(paragraphTbf);
                cursor.insertText(errorFile + ":", heading3);

                for (QStringList::const_iterator it = v.begin(); it != v.end(); ++it) {
                    stringstream instream(it->toStdString());
                    PPErrors err;
                    instream >> err;
                    for (int i = 0; i < PPErrors::NumErrorTypes; ++i) {
                        if (err.isSet(i)) {
//                            stringstream ss;
//                            ss << PPErrors::getText(static_cast<PPErrors::ErrorType> (i));
                            cursor.insertBlock(indentedTbf);
                            cursor.insertText(PPErrors::getText(static_cast<PPErrors::ErrorType> (i)), bodyText);
                        }
                    }
                }
            }
        }
    }

    cursor.movePosition(QTextCursor::End);

    if (resultRows == 0) {
        cursor.insertBlock(indentedTbf);
        cursor.insertText("No matching data found.", bodyText);
    }
}

void ResultsManagerImpl::getOneFishDataSummary(QTextCursor& cursor, const PPRunInfo& runInfo, const QString &target) {
    RunConfigVector runConfig = runInfo.getRunConfig();
    if (runConfig.size() == 0) {
        cursor.insertBlock(indentedTbf);
        cursor.insertText("No matching data found.", bodyText);
    } else {
        for (RunConfigVector::const_iterator it = runConfig.begin(); it != runConfig.end(); ++it) {
            const RunConfigItem& runItem = *it;
            cursor.insertBlock(paragraphTbf);
            cursor.insertText(runItem.name + ":", heading2);
            getOneFishRunTable(cursor, runInfo, runItem, target);
        }
    }
}

/*
void ResultsManagerImpl::getOneFishCaptHistTable(QTextCursor& cursor, const PPRunInfo& runInfo, const string& prefix, const string& target ) {
}
 */

typedef struct {
    QString site;
    QString coil;
    double time;
    QString detector;
    QString outcome;
    QString src;
    QString name;
} Rec;

struct rec_sort : public std::binary_function<const Rec&, const Rec&, bool> {

    bool operator() (const Rec& o1, const Rec & o2) {
        return o1.time < o2.time;
    }
};

void ResultsManagerImpl::getOneFishRunTable(QTextCursor& cursor, const PPRunInfo& runInfo, const RunConfigItem& runItem, const QString &target) {
    const QString dataDir = runInfo.getDataDir();
    QList<Rec> dets;

    //tag data
    QStringList tagrows = getMatchingRows(dataDir, runItem.tag, target);
    qApp->processEvents();
    for (QStringList::const_iterator it = tagrows.begin(); it != tagrows.end(); ++it) {
        stringstream instream(it->toStdString());
        PPTag tag;
        instream >> tag;
        Rec rec;
        rec.site = tag.getRelSite();
        rec.name = tag.getRelSite();
        rec.coil = "";
        rec.time = tag.getRelTime();
        rec.src = runItem.tag;
        rec.outcome = "";
        rec.detector = "RELEASE";

        dets.push_back(rec);
    }

    //interrogation data
    QStringList obsrows = getMatchingRows(dataDir, runItem.obs, target);
    qApp->processEvents();
    for (QStringList::const_iterator it = obsrows.begin(); it != obsrows.end(); ++it) {
        stringstream instream(it->toStdString());
        PPObs obs;
        instream >> obs;
        Rec rec;
        rec.site = obs.getObsSite();
        rec.coil = obs.getCoil();
        rec.time = obs.getTime();
        rec.src = runItem.obs;
        Sites* sites = Sites::getInstance();
        const Detector* det = sites->getDetector(rec.site, rec.coil, rec.time);
        if (det) {
            CbrPit& cp = CbrPit::getInstance();
            rec.outcome = cp.labelFromOutcome(det->getOutcome());
            rec.detector = det->getDetectorName();
        }
        Site* site = sites->getSite(obs.getObsSite());
        if (site)
            rec.name = site->getShortName();

        dets.push_back(rec);
    }

    // recap data
    QStringList recaps = getMatchingRows(dataDir, runItem.recap, target);
    qApp->processEvents();
    for (QStringList::const_iterator it = recaps.begin(); it != recaps.end(); ++it) {
        stringstream instream(it->toStdString());
        PPRecap recap;
        instream >> recap;
        Rec rec;
        rec.site = recap.getSite();
        rec.name = recap.getSite();
        rec.coil = "";
        rec.time = recap.getTime();
        rec.src = runItem.recap;
        rec.outcome = "";
        rec.detector = "RECAPTURE";
        dets.push_back(rec);
    }

    // mort data
    QStringList morts = getMatchingRows(dataDir, runItem.mort, target);
    qApp->processEvents();
    for (QStringList::const_iterator it = morts.begin(); it != morts.end(); ++it) {
        stringstream instream(it->toStdString());
        PPRecap mort;
        instream >> mort;
        Rec rec;
        rec.site = mort.getSite();
        rec.name = mort.getSite();
        rec.coil = "";
        rec.time = mort.getTime();
        rec.src = runItem.mort;
        rec.outcome = "";
        rec.detector = "MORTALITY";
        dets.push_back(rec);
    }


    if (dets.size() == 0) {
        cursor.insertBlock(indentedTbf);
        cursor.insertText("No matching data found.", errorText);
    } else {
        QTextTableCellFormat evenRowFormat;
        QTextTableCellFormat oddRowFormat;

        sort(dets.begin(), dets.end(), rec_sort());

        bool even = false;
        QString prev;

        int col = 0;
        cursor.insertBlock(paragraphTbf);
        QTextTable* table = cursor.insertTable(dets.size() + 1, 6, tableFormat);
        setRowHeaderFormats(table, 0);
        table->cellAt(0, col++).firstCursorPosition().insertText("Site", tableHeaderFormat);
        table->cellAt(0, col++).firstCursorPosition().insertText("Obs Date", tableHeaderFormat);
        table->cellAt(0, col++).firstCursorPosition().insertText("Outcome", tableHeaderFormat);
        table->cellAt(0, col++).firstCursorPosition().insertText("Detector", tableHeaderFormat);
        table->cellAt(0, col++).firstCursorPosition().insertText("Coil", tableHeaderFormat);
        table->cellAt(0, col++).firstCursorPosition().insertText("Source", tableHeaderFormat);

        int row = 1;
        for (QList<Rec>::iterator it = dets.begin(); it != dets.end(); ++it) {
            const Rec& rec = *it;
            if (prev.isEmpty() || prev.compare(rec.name) != 0) {
                prev = rec.name;
                even = !even;
            }

            QTextTableCellFormat cellFormat = even ? evenRowFormat : oddRowFormat;

//            stringstream ss;
//            ss << DateConverter(rec.time);
            QString date(DateConverter(rec.time).output());// = ss.str();
            int col = 0;
            table->cellAt(row, col++).firstCursorPosition().insertText(rec.site, cellFormat);
            table->cellAt(row, col++).firstCursorPosition().insertText(date, cellFormat);
            table->cellAt(row, col++).firstCursorPosition().insertText(rec.outcome, cellFormat);
            table->cellAt(row, col++).firstCursorPosition().insertText(rec.detector, cellFormat);
            table->cellAt(row, col++).firstCursorPosition().insertText(rec.coil, cellFormat);
            table->cellAt(row, col++).firstCursorPosition().insertText(rec.src, cellFormat);

            row++;
        }
    }

    cursor.movePosition(QTextCursor::End);
}

void ResultsManagerImpl::getOneFishOutput(QTextCursor& cursor, const PPRunInfo& runInfo, const QString &prefix, const QString &target) {
    stringstream ss;

    // search in the capture history files
    PitProSettings& settings = PitProSettings::getInstance();
    QString outputDir = runInfo.getOutputDir();

    cursor.insertBlock(paragraphTbf);
    cursor.insertText("Capture History Output:", heading2);
    getMatchingData(cursor, outputDir, prefix + "." + settings.getValue(PitProSettings::SurphSuffix), target);
    qApp->processEvents();

    // search in the output files
    QStringList runNames(runInfo.getRunNames());
    vector<StringPair> outputs;
    outputs.push_back(StringPair("Sequence", settings.getValue(PitProSettings::SeqSuffix)));
    outputs.push_back(StringPair("Error", settings.getValue(PitProSettings::ErrorSuffix)));
    outputs.push_back(StringPair("Travel Time", settings.getValue(PitProSettings::TtSuffix)));
    outputs.push_back(StringPair("Detection Date", settings.getValue(PitProSettings::DdSuffix)));

    for (vector<StringPair>::iterator it = outputs.begin(); it != outputs.end(); ++it) {
        StringPair& pair = *it;
        cursor.insertBlock(paragraphTbf);
        cursor.insertText(QString(pair.first) + " File(s)", heading2);
        getMatchingData(cursor, outputDir, runNames, pair.second, target);
        qApp->processEvents();
    }
}

void ResultsManagerImpl::getOneFishData(QTextCursor& cursor, const PPRunInfo& runInfo, const QString &target) {

    // search in the data files
    vector<StringVectorPair> inputs;
    inputs.push_back(StringVectorPair("Observation", runInfo.getObsFiles()));
    inputs.push_back(StringVectorPair("Tag", runInfo.getTagFiles()));
    inputs.push_back(StringVectorPair("Recapture", runInfo.getRecapFiles()));
    inputs.push_back(StringVectorPair("Mortality", runInfo.getMortFiles()));

    QString dataDir = runInfo.getDataDir();

    for (vector<StringVectorPair>::iterator it = inputs.begin(); it != inputs.end(); ++it) {
        StringVectorPair& pair = *it;
        cursor.insertBlock(paragraphTbf);
        cursor.insertText(QString(pair.first) + " File(s)", heading2);
        getMatchingData(cursor, dataDir, pair.second, target);
        qApp->processEvents();
    }
}

void ResultsManagerImpl::getMatchingData(QTextCursor& cursor, const QString& dir, const QStringList& prefixes, const QString& suffix,
        const QString& target) {
    if (prefixes.size() == 0) {
        cursor.insertBlock(indentedTbf);
        cursor.insertText("No matching data found.", bodyText);
    } else {
        for (QStringList::const_iterator it = prefixes.begin(); it != prefixes.end(); ++it) {
            getMatchingData(cursor, dir, *it + "." + suffix, target);
        }
    }
}

void ResultsManagerImpl::getMatchingData(QTextCursor& cursor, const QString &dir, const QStringList &files, const QString &target) {
    if (files.size() == 0) {
        cursor.insertBlock(indentedTbf);
        cursor.insertText("No matching data found.", bodyText);
    } else {
        for (QStringList::const_iterator it = files.begin(); it != files.end(); ++it) {
            getMatchingData(cursor, dir, *it, target);
        }
    }
}

void ResultsManagerImpl::getMatchingData(QTextCursor& cursor, const QString &dir, const QString &file, const QString &target) {
    QStringList v = getMatchingRows(dir, file, target);

    if (v.size() == 0) {
        cursor.insertBlock(indentedTbf);
        cursor.insertText("No matching data found.", bodyText);
    } else {
        cursor.insertBlock(paragraphTbf);
        cursor.insertText(file + ":", heading3);
        cursor.insertBlock(indentedTbf);

        for (QStringList::iterator it = v.begin(); it != v.end(); it++) {
            if (it != v.begin())
                cursor.insertBlock(indentedLinebreakTbf);
            cursor.insertText((*it), fixedText);
        }
    }
}

QStringList ResultsManagerImpl::getMatchingRows(const QString &dir, const QString &file, const QString &target) {
    QStringList v;

    // open the appropriate file
    QString path = dir + "/" + file;
    ifstream is(path.toStdString().data());

    if (is.is_open()) {
        string line;
        while (getline(is, line)) {
            // if the data is csv replace missing values
            if (line.find(target.toStdString()) != string::npos && line[0] != '#')
                v.push_back(line.data());
        }

        is.close();
    }
    return v;
}

QStringList ResultsManagerImpl::getTrackedPits() {
    QStringList trackedPits;
    for (int i = 0; i < pitComboBox->count(); ++i) {
        trackedPits.append(pitComboBox->itemText(i));
    }
    return trackedPits;
}

void ResultsManagerImpl::setTrackedPits(const QStringList& trackedPits) {
    pitComboBox->addItems(trackedPits);
}

QString ResultsManagerImpl::getSelectedPrefix() {
    return groupCombo->currentText();
}

void ResultsManagerImpl::setSelectedPrefix(const QString& prefix) {
    int index = groupCombo->findText(prefix);
    if (index != -1)
        groupCombo->setCurrentIndex(index);//setCurrentText(prefix);
}

void ResultsManagerImpl::onTrackerDetailChecked(int checkState) {
    PPSystemSettings::getInstance().set(PPSystemSettings::ShowTrackerDetails, checkState == Qt::Checked);
    trackPitCode();
}

void ResultsManagerImpl::onShowOneTableCjsChecked(int checkState) {
    PPSystemSettings::getInstance().set(PPSystemSettings::OneTableCjs, checkState == Qt::Checked);
    staleCjsPage = true;
    updateCjsPage();
}

void ResultsManagerImpl::onShowLambdaChecked(int checkState) {
    PPSystemSettings::getInstance().set(PPSystemSettings::ShowLambda, checkState == Qt::Checked);
    staleCjsPage = true;
    updateCjsPage();
}

void ResultsManagerImpl::setTableHeaderFormats(QTextTable* table, int headerRows) {
    for (int i = 0; i < headerRows; ++i)
        setRowHeaderFormats(table, i);
    setColHeaderFormats(table, 0);
}

void ResultsManagerImpl::setRowHeaderFormats(QTextTable* table, int row) {
    setRowFormats(table, row, tableHeaderFormat, centerTbf);
}

void ResultsManagerImpl::setRowFormats(QTextTable* table, int row, QTextTableCellFormat& cellFormat, QTextBlockFormat& blockFormat) {
    if (row < table->rows()) {
        for (int i = 0; i < table->columns(); ++i) {
            table->cellAt(row, i).setFormat(cellFormat);
            table->cellAt(row, i).firstCursorPosition().setBlockFormat(blockFormat);
        }
    }
}

void ResultsManagerImpl::setColHeaderFormats(QTextTable* table, int col) {
    setColFormats(table, col, tableHeaderFormat, centerTbf);
}

void ResultsManagerImpl::setColFormats(QTextTable* table, int col, QTextTableCellFormat& cellFormat, QTextBlockFormat& blockFormat) {
    if (col < table->columns()) {
        for (int i = 0; i < table->rows(); ++i) {
            table->cellAt(i, col).setFormat(cellFormat);
            table->cellAt(i, col).firstCursorPosition().setBlockFormat(blockFormat);
        }
    }
}

bool ResultsManagerImpl::isNumber(double x) {
    // This looks like it should always be true,
    // but it's false if x is a NaN.
    return (x == x);
}

bool ResultsManagerImpl::isFiniteNumber(double x) {
    return (x <= DBL_MAX && x >= -DBL_MAX);
}

QString ResultsManagerImpl::formatEstimate(double est, const int p) {
    if (!isNumber(est))
        return "NaN";
    else if (!isFiniteNumber(est))
        return "Inf";
    else
        return QString::number(est, 'f', p);
}

QString ResultsManagerImpl::formatSe(double var, const int p) {
    if (!isNumber(var) || var < 0)
        return "NaN";
    else if (!isFiniteNumber(var))
        return "Inf";
    else
        return QString::number(sqrt(var), 'f', p);
}

QTextCursor ResultsManagerImpl::clearFrame(QTextEdit* edit) {
    edit->clear();
    QTextCursor cursor = edit->textCursor();
    QTextFrame* currentFrame = cursor.currentFrame();
    currentFrame->setFrameFormat(frameFormat);
    return cursor;
}

void ResultsManagerImpl::doSummaryAnchorClicked(const QUrl& url) {
    PitProSettings& settings = PitProSettings::getInstance();
    QDir outDir(settings.getValue(PitProSettings::OutputDir));

    statusBar()->showMessage("Loading content...");

    QFile file(outDir.filePath(url.toLocalFile()));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    summaryTextBrowser->document()->clear();
    summaryTextBrowser->setFont(fixedFont);

    QTextStream in(&file);
    summaryTextBrowser->setPlainText(in.readAll());

    statusBar()->showMessage("");

}

void ResultsManagerImpl::doDataAnchorClicked(const QUrl& url) {
    QString prefix = groupCombo->currentText();
    statusBar()->showMessage("Loading content...");

    PPRunInfo& runInfo = PPRunInfo::instance();
    if (runInfo.load(prefix)) {
        QDir outDir(runInfo.getDataDir());

        QFile file(outDir.filePath(url.toLocalFile()));
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

        dataTextBrowser->document()->clear();
        dataTextBrowser->setFont(fixedFont);

        QTextStream in(&file);
        dataTextBrowser->setPlainText(in.readAll());
    }
    statusBar()->showMessage("");

}
