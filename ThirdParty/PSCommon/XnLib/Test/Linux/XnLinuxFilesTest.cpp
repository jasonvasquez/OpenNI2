#include <gtest/gtest.h>
#include <XnOS.h>

TEST(XnLinuxFilesTest, xnOSIsAbsoluteFilePath)
{
	EXPECT_EQ(FALSE, xnOSIsAbsoluteFilePath("c:/a"));
	EXPECT_EQ(FALSE, xnOSIsAbsoluteFilePath("http://"));
	EXPECT_EQ(FALSE, xnOSIsAbsoluteFilePath("c:"));
	EXPECT_EQ(TRUE, xnOSIsAbsoluteFilePath("/abc.txt"));
	EXPECT_EQ(FALSE, xnOSIsAbsoluteFilePath(""));
}
