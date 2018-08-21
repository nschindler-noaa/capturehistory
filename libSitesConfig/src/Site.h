/*
*
*/

#ifndef Site_h
#define Site_h

#include <string>
#include <vector>

#include "ArrayDefs.h"
#include "CbrPit.h"
#include "RiverKm.h"

class Site 
{
public:
    Site (int id, const std::string& codeName);
    ~Site ();

    enum RkType {RK_Up=0, RK_Down};

    bool siteMatch (const std::string& obssite) const;
    bool stageMatch (const std::string& stage) const;
    bool stageMatch (cbr::CbrPit::Stage stage) const;
    int isTrap () const;
    int isAcclimation () const;
    bool isReturned() const;
    bool validRiverkm() const;
    bool isRiverkRange() const;
    bool isAdult() const;
    bool isJuvenile() const;

    /*
    * These functions help find the site in a sequence of sites. The comparison with the target sites may
    * be with the upstream riverk or the downstream riverk for sites where these differ. The comparison 
    * with this object is always made in reference to the RK_Down site (riverkDn_)
    */
    bool isBetween( const Site* sitea, const Site* siteb, RkType rkaType = RK_Down,  RkType rkbType = RK_Down ) const;
    bool isDownstream ( const Site* site, RkType rkType = RK_Down ) const;  
    bool isUpstream ( const Site* site, RkType rkType = RK_Down ) const;
    bool isColocated( const Site* site, RkType rkType = RK_Down ) const;


    // mutators
    void setShortName (const std::string& shortName);
    void setLongName (const std::string& longName);
    void addCode (const std::string& code);
    void addCoilReturned (const std::string& code);
	void setRiverKm (const std::string& riverkUp);
	void setRiverKm (const std::string& riverkDn, const std::string& riverkUp);
    void setType (const std::string& type);
    void setStage (const std::string& stage);
    void setHuc (const std::string& huc);
    void setIndicator (const std::string& indicator);
    void addStage (const std::string& stage);
    void setReleaseSite (bool rhs) { releaseSite_ = rhs; }

    // accessors
    int getId () const { return id_; }
    const std::string& getSiteCode () const { return siteCode_; }
    const std::string& getShortName () const { return shortName_; }
    const std::string& getLongName () const { return longName_; }
    const std::string& getType () const { return type_; }
    const cbr::StringVector& getStages () const { return stages_; }
    const cbr::StringVector& getCodes () const { return codes_; } 
    const cbr::RiverKm& getRiverKm( RkType rkType = RK_Down ) const;
    const cbr::RiverKm& getRiverkDn() const { return riverkDn_; }  
    const cbr::RiverKm& getRiverkUp() const { return riverkUp_; }    

    inline int operator == ( const Site& site ) const
    {
        return id_ == site.id_;
    }
    inline int operator != ( const Site& site ) const
    {
        return id_ != site.id_;
    }
    inline int operator < ( const Site& site ) const
    {
        return id_ < site.id_;
    }
    inline int operator > ( const Site& site ) const
    {
        return id_ > site.id_;
    }

    friend std::ostream &operator <<( std::ostream &o, const Site &site );

private:
    int id_;
    std::string siteCode_;
    std::string shortName_;
    std::string longName_;
    cbr::RiverKm riverkUp_;
    cbr::RiverKm riverkDn_;
    std::string type_;
    std::string huc_;
    std::string indicator_;
    int totalk_;
    bool releaseSite_;
    cbr::StringVector codes_;
    cbr::StringVector stages_;

};

#endif


