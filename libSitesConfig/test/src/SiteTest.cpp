/*
*/

#include <string>

#include <gtest/gtest.h>

#include <Site.h>

#include "SiteTest.h"

using std::string;

SiteTest::SiteTest() : gr_(0), snaker_(0)
{
	gr_ = new Site(0, "gr");
	gr_->setRiverKm("522.173");

	snaker_ = new Site(1, "SNAKER");
	snaker_->setRiverKm("522", "522.397");
}

SiteTest::~SiteTest()
{
	delete gr_;
	delete snaker_;
}

TEST_F(SiteTest, IsDownstream)
{
	ASSERT_FALSE(gr_->isDownstream(snaker_));
	ASSERT_FALSE(gr_->isDownstream(snaker_, Site::RK_Down));
	ASSERT_TRUE(gr_->isDownstream(snaker_, Site::RK_Up));
	ASSERT_TRUE(snaker_->isDownstream(gr_));
	ASSERT_FALSE(gr_->isDownstream(gr_)) << "Comparison with self, no upstream riverk";
	ASSERT_FALSE(snaker_->isDownstream(snaker_)) << "Comparison with self, downstream riverk";
	ASSERT_TRUE(snaker_->isDownstream(snaker_, Site::RK_Up)) << "Comparison with self, upstream riverk";
}

TEST_F(SiteTest, IsUpstream) {
	ASSERT_FALSE(snaker_->isUpstream(gr_, Site::RK_Up));
	ASSERT_TRUE(gr_->isUpstream(snaker_));
	ASSERT_TRUE(gr_->isUpstream(snaker_, Site::RK_Down));
	ASSERT_FALSE(gr_->isUpstream(snaker_, Site::RK_Up));
	ASSERT_FALSE(gr_->isUpstream(gr_));
	ASSERT_FALSE(snaker_->isUpstream(snaker_));
	ASSERT_FALSE(snaker_->isUpstream(snaker_, Site::RK_Up));
}

TEST_F(SiteTest, IsColocated) {
	ASSERT_TRUE(gr_->isColocated(gr_));
	ASSERT_TRUE(snaker_->isColocated(snaker_));
}                                             
