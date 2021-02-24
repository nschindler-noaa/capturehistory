/*
*
*/

#ifndef Site_h
#define Site_h

//#include <string>
//#include <vector>

#include <QStringList>

#include "ArrayDefs.h"
#include "CbrPit.h"
#include "RiverKm.h"

class Site
{
public:
    Site (int id, const QString codeName);
    ~Site ();

    enum RkType {RK_Up=0, RK_Down};

    bool siteMatch (const QString obssite) const;
    bool stageMatch (const QString stage) const;
    bool stageMatch (cbr::CbrPit::Stage stage) const;
    int isTrap () const;
    int isAcclimation () const;
    bool isReturned() const;
    bool validRiverkm() const;
    bool isRiverkRange() const;
    bool isAdult() const;
    bool isJuvenile() const;

    /*
    * These functions help find the site in a sequence of sites.
    * The comparison with the target sites may be with the upstream riverk or
    * the downstream riverk for sites where these differ. The comparison with
    * this object is always made in reference to the RK_Down site (riverkDn_).
    */
    bool isBetween (const Site* sitea, const Site* siteb,
                    RkType rkaType = RK_Down,  RkType rkbType = RK_Down) const;
    bool isDownstream (const Site* site, RkType rkType = RK_Down) const;
    bool isUpstream (const Site* site, RkType rkType = RK_Down) const;
    bool isColocated (const Site* site, RkType rkType = RK_Down) const;


    // mutators
    void setShortName (const QString shortName);
    void setLongName (const QString longName);
    void addCode (const QString code);
    void addCoilReturned (const QString code);
    void setRiverKm (const QString riverkUp);
    void setRiverKm (const QString riverkDn, const QString riverkUp);
    void setType (const QString type);
    void setStage (const QString stage);
    void setHuc (const QString huc);
    void setIndicator (const QString indicator);
    void addStage (const QString stage);
    void setReleaseSite (bool rhs) {releaseSite_ = rhs;}

    // accessors
    int getId () const {return id_;}
    const QString getSiteCode () const {return siteCode_;}
    const QString getShortName () const {return shortName_;}
    const QString getLongName () const {return longName_;}
    const QString getType () const {return type_;}
    const QStringList& getStages () const {return stages_;}
    const QStringList& getCodes () const {return codes_;}
    const cbr::RiverKm& getRiverKm (RkType rkType = RK_Down) const;
    const cbr::RiverKm& getRiverkDn () const {return riverkDn_;}
    const cbr::RiverKm& getRiverkUp () const {return riverkUp_;}

    inline int operator == (const Site& site) const
    {
        return id_ == site.id_;
    }
    inline int operator != (const Site& site) const
    {
        return id_ != site.id_;
    }
    inline int operator < (const Site& site) const
    {
        return id_ < site.id_;
    }
    inline int operator > (const Site& site) const
    {
        return id_ > site.id_;
    }

    friend std::ostream &operator << (std::ostream &o, const Site &site);

private:
    int id_;
    QString siteCode_;
    QString shortName_;
    QString longName_;
    cbr::RiverKm riverkUp_;
    cbr::RiverKm riverkDn_;
    QString type_;
    QString huc_;
    QString indicator_;
    int totalk_;
    bool releaseSite_;
    bool activeSite_;
    bool mainSite_;
    bool lastSite_;
    QStringList codes_;
    QStringList stages_;

};

#endif


