/**
 * New/updated tests: aschiffler at ferzkopp dot net
 */
#include <SDL3/SDL.h>
#include <SDL3/SDL_test.h>
#include "testautomation_suites.h"

/* ================= Test Case Implementation ================== */

/* Test case functions */

/**
 * \brief Check call to SDL_HasClipboardText
 *
 * \sa SDL_HasClipboardText
 */
static int clipboard_testHasClipboardText(void *arg)
{
    SDL_HasClipboardText();
    SDLTest_AssertPass("Call to SDL_HasClipboardText succeeded");

    return TEST_COMPLETED;
}

/**
 * \brief Check call to SDL_HasClipboardData
 *
 * \sa SDL_HasClipboardData
 */
static int clipboard_testHasClipboardData(void *arg)
{
    SDL_HasClipboardData("image/png");
    SDLTest_AssertPass("Call to SDL_HasClipboardData succeeded");

    return TEST_COMPLETED;
}

/**
 * \brief Check call to SDL_HasPrimarySelectionText
 *
 * \sa SDL_HasPrimarySelectionText
 */
static int clipboard_testHasPrimarySelectionText(void *arg)
{
    SDL_HasPrimarySelectionText();
    SDLTest_AssertPass("Call to SDL_HasPrimarySelectionText succeeded");

    return TEST_COMPLETED;
}

/**
 * \brief Check call to SDL_GetClipboardText
 *
 * \sa SDL_GetClipboardText
 */
static int clipboard_testGetClipboardText(void *arg)
{
    char *charResult;
    charResult = SDL_GetClipboardText();
    SDLTest_AssertPass("Call to SDL_GetClipboardText succeeded");

    SDL_free(charResult);

    return TEST_COMPLETED;
}

/**
 * \brief Check call to SDL_GetClipboardData
 *
 * \sa SDL_GetClipboardText
 */
static int clipboard_testGetClipboardData(void *arg)
{
    void *buffer = NULL;
    size_t length;
    buffer = SDL_GetClipboardData(&length, "image/png");
    SDLTest_AssertPass("Call to SDL_GetClipboardData succeeded");

    if (buffer != NULL) {
        SDL_free(buffer);
    }

    return TEST_COMPLETED;
}

/**
 * \brief Check call to SDL_GetPrimarySelectionText
 *
 * \sa SDL_GetPrimarySelectionText
 */
static int clipboard_testGetPrimarySelectionText(void *arg)
{
    char *charResult;
    charResult = SDL_GetPrimarySelectionText();
    SDLTest_AssertPass("Call to SDL_GetPrimarySelectionText succeeded");

    SDL_free(charResult);

    return TEST_COMPLETED;
}

/**
 * \brief Check call to SDL_SetClipboardText
 * \sa SDL_SetClipboardText
 */
static int clipboard_testSetClipboardText(void *arg)
{
    char *textRef = SDLTest_RandomAsciiString();
    char *text = SDL_strdup(textRef);
    int result;
    result = SDL_SetClipboardText((const char *)text);
    SDLTest_AssertPass("Call to SDL_SetClipboardText succeeded");
    SDLTest_AssertCheck(
        result == 0,
        "Validate SDL_SetClipboardText result, expected 0, got %i",
        result);
    SDLTest_AssertCheck(
        SDL_strcmp(textRef, text) == 0,
        "Verify SDL_SetClipboardText did not modify input string, expected '%s', got '%s'",
        textRef, text);

    /* Cleanup */
    SDL_free(textRef);
    SDL_free(text);

    return TEST_COMPLETED;
}

/**
 * \brief Check call to SDL_SetClipboardData
 * \sa SDL_SetClipboardText
 */
static int clipboard_testSetClipboardData(void *arg)
{
    int result = -1;

    result = SDL_SetClipboardData(NULL, 0, NULL, NULL);
    SDLTest_AssertPass("Call to SDL_SetClipboardData succeeded");
    SDLTest_AssertCheck(
        result == 0,
        "Validate SDL_SetClipboardData result, expected 0, got %i",
        result);

    SDL_GetClipboardUserdata();
    SDLTest_AssertPass("Call to SDL_GetClipboardUserdata succeeded");

    return TEST_COMPLETED;
}

/**
 * \brief Check call to SDL_SetPrimarySelectionText
 * \sa SDL_SetPrimarySelectionText
 */
static int clipboard_testSetPrimarySelectionText(void *arg)
{
    char *textRef = SDLTest_RandomAsciiString();
    char *text = SDL_strdup(textRef);
    int result;
    result = SDL_SetPrimarySelectionText((const char *)text);
    SDLTest_AssertPass("Call to SDL_SetPrimarySelectionText succeeded");
    SDLTest_AssertCheck(
        result == 0,
        "Validate SDL_SetPrimarySelectionText result, expected 0, got %i",
        result);
    SDLTest_AssertCheck(
        SDL_strcmp(textRef, text) == 0,
        "Verify SDL_SetPrimarySelectionText did not modify input string, expected '%s', got '%s'",
        textRef, text);

    /* Cleanup */
    SDL_free(textRef);
    SDL_free(text);

    return TEST_COMPLETED;
}

/**
 * \brief End-to-end test of SDL_xyzClipboardText functions
 * \sa SDL_HasClipboardText
 * \sa SDL_GetClipboardText
 * \sa SDL_SetClipboardText
 */
static int clipboard_testClipboardTextFunctions(void *arg)
{
    char *textRef = SDLTest_RandomAsciiString();
    char *text = SDL_strdup(textRef);
    SDL_bool boolResult;
    int intResult;
    char *charResult;

    /* Clear clipboard text state */
    boolResult = SDL_HasClipboardText();
    SDLTest_AssertPass("Call to SDL_HasClipboardText succeeded");
    if (boolResult == SDL_TRUE) {
        intResult = SDL_SetClipboardText((const char *)NULL);
        SDLTest_AssertPass("Call to SDL_SetClipboardText(NULL) succeeded");
        SDLTest_AssertCheck(
            intResult == 0,
            "Verify result from SDL_SetClipboardText(NULL), expected 0, got %i",
            intResult);
        charResult = SDL_GetClipboardText();
        SDLTest_AssertPass("Call to SDL_GetClipboardText succeeded");
        SDL_free(charResult);
        boolResult = SDL_HasClipboardText();
        SDLTest_AssertPass("Call to SDL_HasClipboardText succeeded");
        SDLTest_AssertCheck(
            boolResult == SDL_FALSE,
            "Verify SDL_HasClipboardText returned SDL_FALSE, got %s",
            (boolResult) ? "SDL_TRUE" : "SDL_FALSE");
    }

    /* Empty clipboard  */
    charResult = SDL_GetClipboardText();
    SDLTest_AssertPass("Call to SDL_GetClipboardText succeeded");
    SDLTest_Assert(
        charResult != NULL,
        "Verify SDL_GetClipboardText did not return NULL");
    SDLTest_AssertCheck(
        charResult[0] == '\0', /* NOLINT(clang-analyzer-core.NullDereference): Checked for NULL above */
        "Verify SDL_GetClipboardText returned string with length 0, got length %i",
        (int)SDL_strlen(charResult));
    intResult = SDL_SetClipboardText((const char *)text);
    SDLTest_AssertPass("Call to SDL_SetClipboardText succeeded");
    SDLTest_AssertCheck(
        intResult == 0,
        "Verify result from SDL_SetClipboardText(NULL), expected 0, got %i",
        intResult);
    SDLTest_AssertCheck(
        SDL_strcmp(textRef, text) == 0,
        "Verify SDL_SetClipboardText did not modify input string, expected '%s', got '%s'",
        textRef, text);
    boolResult = SDL_HasClipboardText();
    SDLTest_AssertPass("Call to SDL_HasClipboardText succeeded");
    SDLTest_AssertCheck(
        boolResult == SDL_TRUE,
        "Verify SDL_HasClipboardText returned SDL_TRUE, got %s",
        (boolResult) ? "SDL_TRUE" : "SDL_FALSE");
    SDL_free(charResult);
    charResult = SDL_GetClipboardText();
    SDLTest_AssertPass("Call to SDL_GetClipboardText succeeded");
    SDLTest_AssertCheck(
        SDL_strcmp(textRef, charResult) == 0,
        "Verify SDL_GetClipboardText returned correct string, expected '%s', got '%s'",
        textRef, charResult);

    /* Cleanup */
    SDL_free(textRef);
    SDL_free(text);
    SDL_free(charResult);

    return TEST_COMPLETED;
}

/**
 * \brief End-to-end test of SDL_xyzPrimarySelectionText functions
 * \sa SDL_HasPrimarySelectionText
 * \sa SDL_GetPrimarySelectionText
 * \sa SDL_SetPrimarySelectionText
 */
static int clipboard_testPrimarySelectionTextFunctions(void *arg)
{
    char *textRef = SDLTest_RandomAsciiString();
    char *text = SDL_strdup(textRef);
    SDL_bool boolResult;
    int intResult;
    char *charResult;

    /* Clear primary selection text state */
    boolResult = SDL_HasPrimarySelectionText();
    SDLTest_AssertPass("Call to SDL_HasPrimarySelectionText succeeded");
    if (boolResult == SDL_TRUE) {
        intResult = SDL_SetPrimarySelectionText((const char *)NULL);
        SDLTest_AssertPass("Call to SDL_SetPrimarySelectionText(NULL) succeeded");
        SDLTest_AssertCheck(
            intResult == 0,
            "Verify result from SDL_SetPrimarySelectionText(NULL), expected 0, got %i",
            intResult);
        charResult = SDL_GetPrimarySelectionText();
        SDLTest_AssertPass("Call to SDL_GetPrimarySelectionText succeeded");
        SDL_free(charResult);
        boolResult = SDL_HasPrimarySelectionText();
        SDLTest_AssertPass("Call to SDL_HasPrimarySelectionText succeeded");
        SDLTest_AssertCheck(
            boolResult == SDL_FALSE,
            "Verify SDL_HasPrimarySelectionText returned SDL_FALSE, got %s",
            (boolResult) ? "SDL_TRUE" : "SDL_FALSE");
    }

    /* Empty primary selection  */
    charResult = SDL_GetPrimarySelectionText();
    SDLTest_AssertPass("Call to SDL_GetPrimarySelectionText succeeded");
    SDLTest_Assert(
        charResult != NULL,
        "Verify SDL_GetPrimarySelectionText did not return NULL");
    SDLTest_AssertCheck(
        charResult[0] == '\0', /* NOLINT(clang-analyzer-core.NullDereference): Checked for NULL above */
        "Verify SDL_GetPrimarySelectionText returned string with length 0, got length %i",
        (int)SDL_strlen(charResult));
    intResult = SDL_SetPrimarySelectionText((const char *)text);
    SDLTest_AssertPass("Call to SDL_SetPrimarySelectionText succeeded");
    SDLTest_AssertCheck(
        intResult == 0,
        "Verify result from SDL_SetPrimarySelectionText(NULL), expected 0, got %i",
        intResult);
    SDLTest_AssertCheck(
        SDL_strcmp(textRef, text) == 0,
        "Verify SDL_SetPrimarySelectionText did not modify input string, expected '%s', got '%s'",
        textRef, text);
    boolResult = SDL_HasPrimarySelectionText();
    SDLTest_AssertPass("Call to SDL_HasPrimarySelectionText succeeded");
    SDLTest_AssertCheck(
        boolResult == SDL_TRUE,
        "Verify SDL_HasPrimarySelectionText returned SDL_TRUE, got %s",
        (boolResult) ? "SDL_TRUE" : "SDL_FALSE");
    SDL_free(charResult);
    charResult = SDL_GetPrimarySelectionText();
    SDLTest_AssertPass("Call to SDL_GetPrimarySelectionText succeeded");
    SDLTest_AssertCheck(
        SDL_strcmp(textRef, charResult) == 0,
        "Verify SDL_GetPrimarySelectionText returned correct string, expected '%s', got '%s'",
        textRef, charResult);

    /* Cleanup */
    SDL_free(textRef);
    SDL_free(text);
    SDL_free(charResult);

    return TEST_COMPLETED;
}

/* ================= Test References ================== */

/* Clipboard test cases */
static const SDLTest_TestCaseReference clipboardTest1 = {
    (SDLTest_TestCaseFp)clipboard_testHasClipboardText, "clipboard_testHasClipboardText", "Check call to SDL_HasClipboardText", TEST_ENABLED
};

static const SDLTest_TestCaseReference clipboardTest2 = {
    (SDLTest_TestCaseFp)clipboard_testHasPrimarySelectionText, "clipboard_testHasPrimarySelectionText", "Check call to SDL_HasPrimarySelectionText", TEST_ENABLED
};

static const SDLTest_TestCaseReference clipboardTest3 = {
    (SDLTest_TestCaseFp)clipboard_testGetClipboardText, "clipboard_testGetClipboardText", "Check call to SDL_GetClipboardText", TEST_ENABLED
};

static const SDLTest_TestCaseReference clipboardTest4 = {
    (SDLTest_TestCaseFp)clipboard_testGetPrimarySelectionText, "clipboard_testGetPrimarySelectionText", "Check call to SDL_GetPrimarySelectionText", TEST_ENABLED
};

static const SDLTest_TestCaseReference clipboardTest5 = {
    (SDLTest_TestCaseFp)clipboard_testSetClipboardText, "clipboard_testSetClipboardText", "Check call to SDL_SetClipboardText", TEST_ENABLED
};

static const SDLTest_TestCaseReference clipboardTest6 = {
    (SDLTest_TestCaseFp)clipboard_testSetPrimarySelectionText, "clipboard_testSetPrimarySelectionText", "Check call to SDL_SetPrimarySelectionText", TEST_ENABLED
};

static const SDLTest_TestCaseReference clipboardTest7 = {
    (SDLTest_TestCaseFp)clipboard_testClipboardTextFunctions, "clipboard_testClipboardTextFunctions", "End-to-end test of SDL_xyzClipboardText functions", TEST_ENABLED
};

static const SDLTest_TestCaseReference clipboardTest8 = {
    (SDLTest_TestCaseFp)clipboard_testPrimarySelectionTextFunctions, "clipboard_testPrimarySelectionTextFunctions", "End-to-end test of SDL_xyzPrimarySelectionText functions", TEST_ENABLED
};

static const SDLTest_TestCaseReference clipboardTest9 = {
    (SDLTest_TestCaseFp)clipboard_testGetClipboardData, "clipboard_testGetClipboardData", "Check call to SDL_GetClipboardData", TEST_ENABLED
};

static const SDLTest_TestCaseReference clipboardTest10 = {
    (SDLTest_TestCaseFp)clipboard_testSetClipboardData, "clipboard_testSetClipboardData", "Check call to SDL_SetClipboardData", TEST_ENABLED
};

static const SDLTest_TestCaseReference clipboardTest11 = {
    (SDLTest_TestCaseFp)clipboard_testHasClipboardData, "clipboard_testHasClipboardData", "Check call to SDL_HasClipboardData", TEST_ENABLED
};

/* Sequence of Clipboard test cases */
static const SDLTest_TestCaseReference *clipboardTests[] = {
    &clipboardTest1, &clipboardTest2, &clipboardTest3, &clipboardTest4, &clipboardTest5, &clipboardTest6, &clipboardTest7, &clipboardTest8, &clipboardTest9, &clipboardTest10, &clipboardTest11, NULL
};

/* Clipboard test suite (global) */
SDLTest_TestSuiteReference clipboardTestSuite = {
    "Clipboard",
    NULL,
    clipboardTests,
    NULL
};
