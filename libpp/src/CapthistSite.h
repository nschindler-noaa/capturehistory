/*
 * file: site.h
 *
 */

#ifndef site_h_included
#define site_h_included

#include <stdio.h>

#include <Site.h>

#define NDETS 6

enum JuvenileFlags { UNDETECTED='0', RETURNED='1', 
                     CENSORED='2', TRANSPORTED='3', UNKNOWN='U' };
enum AdultFlags { JACK = 'J', ONEYEAR ='A', TWOYEAR='B', THREEYEAR='C', 
    FOURYEAR='D', FIVEANDOLDER='E' };

enum Route { EXIT=1, RACE=2, SAMP=4, HOLD=8, BYPASS=16, UNKN=32 };

enum {TT, DD, BOTH};

typedef struct {
    Site* config;
    double ftt, ltt, fjd, ljd;
    int hits;
    int isLastField;
    unsigned int any : 1;
    bitfield *coils;
} SiteDet;

#ifdef __cplusplus
extern "C" {
#endif

void SiteInit(SiteDet *site);
SiteDet *SiteCr(int sn);
void SiteDr(SiteDet *site);
void SitePrCoil(FILE *fp, SiteDet *site);
void SitePr(FILE *fp, SiteDet *site, int format);

int SiteHits(SiteDet *site);
char SiteGetHist(SiteDet *site, double relDate);

void SiteAddObs(SiteDet *site, Obs *obs, double relDate);
void SiteSetAny(SiteDet *site);
int SiteAdult(SiteDet *site);
int SiteAnyDetections(SiteDet *site);
int SiteNumber(const char *site);
const char *SiteName(int site);
int SiteCheckForCoilErrors(SiteDet *site, bitfield *bf, int anyDownStreamDets);
int SiteIsLastField(SiteDet *site);
void SiteSetIsLastField(SiteDet *site);


#ifdef __cplusplus
}
#endif

#endif
