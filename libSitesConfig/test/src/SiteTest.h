
#include <string>

class Site;

class SiteTest : public ::testing::Test
{
public:
	SiteTest();
	~SiteTest();
	Site* gr_;
	Site* snaker_;
};