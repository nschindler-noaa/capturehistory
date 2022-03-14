/*
 * ResultsManagerImpl.h
 */

#ifndef ResultsManagerImpl_h
#define ResultsManagerImpl_h

#include <string>
#include <qfile.h>
#include <QMainWindow>
#include <qstringlist.h>
#include <QTextTableFormat>
#include <QTextTableCellFormat>
#include <QTextFrameFormat>
#include <QTextCharFormat>
#include <QTextBlockFormat>
#include <QTextListFormat>

#include <ArrayDefs.h>

#include "ui_ResultsManager.h"
#include "RunConfigVector.h"

class QFileInfo;
class QTextTable;

class TextWindow;
//class PPStyleSheet;
class PPRunInfo;
class TaggingData;
class CjsEstimates;

namespace surph {
    class SurphData;
}

class ResultsManagerImpl : public QMainWindow, public Ui::ResultsManager {
    Q_OBJECT

public:
    ResultsManagerImpl(QWidget* parent = 0, const QString name = QString(""), Qt::WindowFlags fl = 0);
    ~ResultsManagerImpl();

    QStringList getTrackedPits();
    void setTrackedPits(const QStringList& trackedPits);
    QString getSelectedPrefix();
    void setSelectedPrefix(const QString& prefix);

public slots:
    void setStale(bool rhs = true);
    void setGroup(const QString&);

private slots:
    void currentTabChanged(QWidget*);
    void updateTtPage(const QString& run);
    void updateErrorsPage(const QString& run);

    void summaryPageHome();
    void dataSummaryPageHome();
    void outputDirChanged(const QString&);
    void trackPitCode();
    void doCjsData();
    void doCovarianceMatrix();
    void doTTData();
    void doPrint();
    void doSave();
    void onTrackerDetailChecked(int);
    void onShowLambdaChecked(int);
    void onShowOneTableCjsChecked(int);

    void doSummaryAnchorClicked(const QUrl&);
    void doDataAnchorClicked(const QUrl&);

private:

    enum ResultsType {
        AMEAN, ASE, HMEAN, HSE, COUNT
    };

    int p; // output field precision
    QFont fixedFont;
    QTextCharFormat bodyText;
    QTextCharFormat italicText;
    QTextCharFormat fixedText;
    QTextCharFormat boldText;
    QTextCharFormat errorText;
    QTextCharFormat heading1;
    QTextCharFormat heading2;
    QTextCharFormat heading3;
    QTextTableFormat tableFormat;
    QTextTableCellFormat tableHeaderFormat;
    QTextTableCellFormat tableDataFormat;
    QTextBlockFormat centerTbf;
    QTextBlockFormat rightTbf;
    QTextBlockFormat leftTbf;
    QTextFrameFormat frameFormat;
    QTextBlockFormat indentedTbf;
    QTextBlockFormat sectionTbf;
    QTextBlockFormat paragraphTbf;
    QTextBlockFormat linebreakTbf;
    QTextBlockFormat indentedLinebreakTbf;
    QTextListFormat listFormat;

    void setTableHeaderFormats(QTextTable* table, int headerRows);
    void setRowHeaderFormats(QTextTable* table, int row);
    void setRowFormats(QTextTable* table, int row, QTextTableCellFormat& cellFormat, QTextBlockFormat& blockFormat);
    void setColHeaderFormats(QTextTable* table, int col);
    void setColFormats(QTextTable* table, int col, QTextTableCellFormat& cellFormat, QTextBlockFormat& blockFormat);

    QTextEdit covarTextEdit;
    QTextEdit cjsDataTextEdit;
    QTextEdit ttDataTextEdit;

    bool staleSummaryPage;
    bool staleSurphPage;
    bool staleErrorsPage;
    bool staleTtPage;
    bool staleCjsPage;
    bool staleDataPage;

    void updateGroupCombo();
    void updateCurrentPage(QWidget* current = 0);
    void updateSummaryPage();
    void updateCjsPage();
    void updateDataPage();

    void getResultsTable(QTextCursor& cursor, const QStringList& headers,
            const cbr::Matrix<cbr::DoubleVector>& ttMatrix, ResultsType type);

    QString getOutputByConfig(const QString& prefix);
    void createDataSummary(QTextCursor& cursor, const QString& prefix);
    void createDataSummaryReport(QTextCursor& cursor, const RunConfigItem& runItem);
    QString createOutputSummaryReport(const RunConfigItem& runItem);
    void printDataInfoRow(QTextTable* table, int row, const QString &dir, const QString &file);
    void createErrorReport(QTextCursor& cursor, const QString& prefix);
    void createTTTableReport(QTextCursor& cursor, const QStringList& headers, const cbr::Matrix<cbr::DoubleVector>& ttMatrix, const QString& prefix);
    void createTTDataReport(QTextCursor& cursor, const QStringList& headers, const cbr::Matrix<cbr::DoubleVector>& ttMatrix, const QString& prefix);
    void getOutputByPrefix(QTextCursor& cursor, const QString& prefix, bool combined);
    void writeFileInfoHeader(QTextTable* table);
    void writeFileInfoRow(QTextTable* table, int row, const QFileInfo& fi);
    void getCombinedSummaryOutput(QTextCursor& cursor, const QString& prefix);
    void createCjsReport(QTextCursor& cursor, const surph::SurphData& data, QList<CjsEstimates*>& estimates, const QString& prefix);
    void createCjsDataReport(QTextCursor& cursor, const surph::SurphData& data, QList<CjsEstimates*>& estimates, const QString& prefix);
    void createCovarianceReport(QTextCursor& cursor, const surph::SurphData& data, const QString& prefix);

    void getOneFishSummary(QTextCursor& cursor, const PPRunInfo& runInfo, const QString& prefix, const QString& target);
    void getOneFishOutputSummary(QTextCursor& cursor, const PPRunInfo& runInfo, const QString& prefix, const QString& target);
    void getOneFishDataSummary(QTextCursor& cursor, const PPRunInfo& runInfo, const QString& target);
    void getOneFishCaptHistTable(QTextCursor& cursor, const PPRunInfo& runInfo, const QString& prefix, const QString& target);
    void getOneFishRunTable(QTextCursor& cursor, const PPRunInfo& runInfo, const RunConfigItem& runItem, const QString& target);
    void getOneFishOutput(QTextCursor& cursor, const PPRunInfo& runInfo, const QString& prefix, const QString& target);
    void getOneFishData(QTextCursor& cursor, const PPRunInfo& runInfo, const QString& target);

    void getMatchingData(QTextCursor& cursor, const QString& dir, const QStringList& files, const QString& target);
    void getMatchingData(QTextCursor& cursor, const QString& dir, const QStringList &prefixes, const QString &suffix, const QString& target);
    void getMatchingData(QTextCursor& cursor, const QString& dir, const QString& obsFile, const QString& target);
    QStringList getMatchingRows(const QString& dir, const QString& file, const QString& target);

    void saveFile(const QString& fileName, const QString& output, const QString& filter);

    // output formatting methods
    bool isNumber(double x);
    bool isFiniteNumber(double x);
    QString formatEstimate(double est, const int p);
    QString formatSe(double var, const int p);

    QTextCursor clearFrame(QTextEdit* edit);

    QString getStageKey(int& numJuvSites) const;

    void insertCjsKey(QTextCursor& cursor, const surph::SurphData& surphData, const QString& prefix, bool showLambda);

};

#endif // ResultsManagerImpl_h
