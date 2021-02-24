Here at last are some files to test various "granularity" situations in capthist.

The data files are "capthist.test.tag" and "capthist.test.obs."  These are all real fish that migrated in 2020.  Some of them passed LGR via the spillway (GRS detector -- we'll get to that later, I think).

The 326 tag ids were chosen for specific reasons -- without getting into too much detail, I think they between them they represent almost all of the ways that juvenile fish can pass the various dams under the obs codes GRS, GRJ, GOJ, LMJ, ICH, MCJ, JDJ, BCC, and B2J.

The two files agr.ppc and juv_sites_config_bvtw.txt are configuration files.

The final file, b.ch.2bv, is a batch file with a call to capthist, with a number of command line flags.  The batch file works in the setting of what is the typical setup for us.  The assumption is that b.ch.2bv and the two configuration files are all in the same directory, which has two subdirectories: "data" and "output."  The tag and obs files are assumed to be in the data subdirectory and the output from capthist is all written to the output directory.

capthist.test.ch.default is the result "ch" file when the batch file b.ch.2bv is run using capthist.test.tag and capthist.test.obs.  That is, this is the *current* output and will remain the result with default settings after the modifications. (histDetail=simple)

capthist.test.ch.option is what would result from histDetail=detail. 