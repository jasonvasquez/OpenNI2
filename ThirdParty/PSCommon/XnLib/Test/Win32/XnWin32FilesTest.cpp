#include <gtest/gtest.h>
#include <XnOS.h>

TEST(XnWin32FilesTest, xnOSGetDirNameRelative)
{
	XnChar dirName[XN_FILE_MAX_PATH];

	EXPECT_EQ(XN_STATUS_OK, xnOSGetDirName("abc\\def\\hij.txt", dirName, XN_FILE_MAX_PATH));

	XnChar expectedDirName[XN_FILE_MAX_PATH];
	xnOSGetCurrentDir(expectedDirName, XN_FILE_MAX_PATH);
	xnOSAppendFilePath(expectedDirName, "abc\\def", XN_FILE_MAX_PATH);

	EXPECT_STREQ(expectedDirName, dirName);
}

TEST(XnWin32FilesTest, xnOSGetDirNameAbsolute)
{
	XnChar dirName[XN_FILE_MAX_PATH];

	EXPECT_EQ(XN_STATUS_OK, xnOSGetDirName("x:\\abc\\def\\hij.txt", dirName, XN_FILE_MAX_PATH));
	EXPECT_STREQ("x:\\abc\\def", dirName);
}

TEST(XnWin32FileTest, xnOSIsAbsoluteFilePath)
{
	EXPECT_EQ(TRUE, xnOSIsAbsoluteFilePath("c:\\a"));
	EXPECT_EQ(FALSE, xnOSIsAbsoluteFilePath("http://"));
	EXPECT_EQ(FALSE, xnOSIsAbsoluteFilePath("c:"));
	EXPECT_EQ(FALSE, xnOSIsAbsoluteFilePath("\\abc.txt"));
	EXPECT_EQ(FALSE, xnOSIsAbsoluteFilePath(""));
}
