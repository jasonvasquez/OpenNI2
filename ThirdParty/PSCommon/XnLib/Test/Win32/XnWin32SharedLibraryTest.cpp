#include <gtest/gtest.h>
#include <XnOS.h>

static void dummyFunc() {}

static bool strEndsWith(const XnChar* s, const XnChar* suffix)
{
	if (strlen(s) >= strlen(suffix)) {
		return strcmp(s + strlen(s) - strlen(suffix), suffix) == 0;
	} else {
		return false;
	}
}

TEST(XnWin32SharedLibraryTest, xnOSGetModulePathForProcAddress)
{
	XnChar strModuleName[XN_FILE_MAX_PATH];

	EXPECT_EQ(XN_STATUS_OK, xnOSGetModulePathForProcAddress(dummyFunc, strModuleName));
	EXPECT_TRUE(strEndsWith(strModuleName, "\\XnLibTest.exe"));
	EXPECT_EQ(TRUE, xnOSIsAbsoluteFilePath(strModuleName));
	// puts(strModuleName);

	EXPECT_EQ(XN_STATUS_OK, xnOSGetModulePathForProcAddress(FormatMessage, strModuleName));
	EXPECT_TRUE(strEndsWith(strModuleName, "\\kernel32.dll"));
	EXPECT_EQ(TRUE, xnOSIsAbsoluteFilePath(strModuleName));
	// puts(strModuleName);

	EXPECT_EQ(XN_STATUS_ERROR, xnOSGetModulePathForProcAddress((void*)-1, strModuleName));
}
