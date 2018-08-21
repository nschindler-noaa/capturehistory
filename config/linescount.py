import os, sys
import glob

apps = [
	"atlas",
	"atlasParser",
	"attools",
	"blt",
	"branch",
	"branchSim",
	"branchGenExpCounts",
	"branchEstimateFromCounts",
	"branchUserModelCreator",
	"capthist",
	"passageTiming",
	"pitpro",
	"surph",
	"samplesize",
	"user",
	"roster"
]

libs = [
	"libAlg",
	"libAtlas",
	"libblt",
	"libBranch",
	"libBranchAuxiliary",
	"libBranchGenExpCounts",
	"libBranchEstimateFromCounts",
	"libBranchSim",
	"libCapthist",
	"libCbrDate",
	"libCbrPlot",
	"libcbrqt4",
	"libcbrstd",
	"libCbrThread",
	"libCbrTypes",
	"libCbrUi",
	"libCjs",
	"libCoordinate",
	"libEquation",
	"libEstimate",
	"libNavPanel",
	"libNumericalRecipes3",
	"libParser",
	"libPassageTiming",
	"libPitObs",
	"libProfileLikelihoods",
	"libpp",
	"libQtReport",
	"libQtSqlite",
	"libroster",
	"libSqliteBrowser",
	"libSitesConfig",
	"libSqlite",
	"libStringUtilities",
	"libStatistics",
	"libsurph",
	"libuser",
	"libxmlutils"
]

def file_len(fname):
	count = 0
	for line in open(fname):
		count += 1
	return count


total_lines = 0

folders = list(set(apps) | set(libs))
for folder in folders:
	dir = '../' + folder + '/src/'
	#files = os.listdir( dir )

   	files = glob.glob(dir + "*.cpp")
	for file in files:
		filelen = file_len(file) 
   		total_lines += filelen


   	files = glob.glob(dir + "*.h")
	for file in files:
		filelen = file_len(file)
   		total_lines += filelen

print total_lines

