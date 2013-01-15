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

TEST(XnLinuxSharedLibs, xnOSGetModulePathForProcAddress)
{
	XnChar strModuleName[XN_FILE_MAX_PATH];

	EXPECT_EQ(XN_STATUS_OK, xnOSGetModulePathForProcAddress(reinterpret_cast<void*>(&dummyFunc), strModuleName));
	EXPECT_TRUE(strEndsWith(strModuleName, "/XnLibTest"));
	//EXPECT_EQ(TRUE, xnOSIsAbsoluteFilePath(strModuleName));
	puts(strModuleName);

	EXPECT_EQ(XN_STATUS_OK, xnOSGetModulePathForProcAddress(reinterpret_cast<void*>(&exit), strModuleName));
	EXPECT_TRUE(strstr(strModuleName, "/libc.so") != NULL);
	EXPECT_EQ(TRUE, xnOSIsAbsoluteFilePath(strModuleName));
	puts(strModuleName);

	EXPECT_EQ(XN_STATUS_ERROR, xnOSGetModulePathForProcAddress(reinterpret_cast<void*>(-1), strModuleName));
}

// TODO(Tomoto):
// Need testing to get the module path from a shared library loaded by relative path.
// The resulted module path must be absolute.
