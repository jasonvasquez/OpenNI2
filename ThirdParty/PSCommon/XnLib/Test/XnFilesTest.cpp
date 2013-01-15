#include <gtest/gtest.h>
#include <XnOS.h>

static void xnOSStripDirSepHelper(const char* strExpected, const char* strInput)
{
	char buf[XN_FILE_MAX_PATH];
	xnOSStrCopy(buf, strInput, XN_FILE_MAX_PATH);
	EXPECT_EQ(XN_STATUS_OK, xnOSStripDirSep(buf));
	EXPECT_STREQ(strExpected, buf);
}

TEST(XnFilesTest, xnOSStripDirSep)
{
	xnOSStripDirSepHelper("", "");
	xnOSStripDirSepHelper("", "/");
	xnOSStripDirSepHelper("/tmp", "/tmp");
	xnOSStripDirSepHelper("/tmp", "/tmp/");

#ifdef _WIN32
	xnOSStripDirSepHelper("", "\\");
	xnOSStripDirSepHelper("C:\\tmp", "C:\\tmp");
	xnOSStripDirSepHelper("C:\\tmp", "C:\\tmp\\");
#else
	xnOSStripDirSepHelper("\\", "\\");
	xnOSStripDirSepHelper("C:\\tmp", "C:\\tmp");
	xnOSStripDirSepHelper("C:\\tmp\\", "C:\\tmp\\");
#endif
}

TEST(XnFilesTest, xnOSIsDirSep)
{
	EXPECT_EQ(FALSE, xnOSIsDirSep('a'));
	EXPECT_EQ(TRUE, xnOSIsDirSep('/'));
#ifdef _WIN32
	EXPECT_EQ(TRUE, xnOSIsDirSep('\\'));
#else
	EXPECT_EQ(FALSE, xnOSIsDirSep('\\'));
#endif

	EXPECT_EQ(FALSE, xnOSIsDirSep('\0'));
}

static void xnOSAppendFilePathHelper(const char* expected, const char* base, const char* suffix)
{
	char buf[XN_FILE_MAX_PATH];
	strcpy(buf, base);
	EXPECT_EQ(XN_STATUS_OK, xnOSAppendFilePath(buf, suffix, XN_FILE_MAX_PATH));
	EXPECT_STREQ(expected, buf);
}

TEST(XnFilesTest, xnOSAppendFilePathWithRelative)
{
#ifdef _WIN32
	xnOSAppendFilePathHelper("c:\\ab\\cd\\e\\f\\g", "c:\\ab\\cd", "e\\f\\g");
	xnOSAppendFilePathHelper("c:\\ab\\e\\f\\g", "c:\\ab", "e\\f\\g");
#else
	xnOSAppendFilePathHelper("/ab/cd/f/g/h", "/ab/cd", "f/g/h");
	xnOSAppendFilePathHelper("/ab/f/g/h", "/ab/", "f/g/h");
#endif

	char buf[XN_FILE_MAX_PATH];
	strcpy(buf, "c:\\ab\\cd");
	EXPECT_EQ(XN_STATUS_INTERNAL_BUFFER_TOO_SMALL, xnOSAppendFilePath(buf, "e\\f\\g", 8));
}

TEST(XnFilesTest, xnOSAppendFilePathWithAbsolute)
{
#ifdef _WIN32
	static const char* const BASE = "c:\\ab\\cd";
	static const char* const SUFFIX = "e:\\f\\g";
#else
	static const char* const BASE = "/ab/cd";
	static const char* const SUFFIX = "/f/g/h";
#endif

	char buf[XN_FILE_MAX_PATH];

	strcpy(buf, BASE);
	EXPECT_EQ(XN_STATUS_OK, xnOSAppendFilePath(buf, SUFFIX, XN_FILE_MAX_PATH));
	EXPECT_STREQ(SUFFIX, buf);

	strcpy(buf, BASE);
	EXPECT_EQ(XN_STATUS_INTERNAL_BUFFER_TOO_SMALL, xnOSAppendFilePath(buf, SUFFIX, 5));
}
