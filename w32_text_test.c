/*--------------
http://www.geocities.jp/ky_webid/win32c/021.html
---------------*/

#include <windows.h>
#include <tchar.h>

// �萔
#define WINDOW_WIDTH  (400)		// �E�B���h�E�̕�
#define WINDOW_HEIGHT (300)		// �E�B���h�E�̍���
#define WINDOW_X ((GetSystemMetrics( SM_CXSCREEN ) - WINDOW_WIDTH ) / 2)
#define WINDOW_Y ((GetSystemMetrics( SM_CYSCREEN ) - WINDOW_HEIGHT ) / 2)

// �v���g�^�C�v�錾
HWND Create(HINSTANCE hInst);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);


// �J�n�ʒu
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR pCmdLine, int showCmd)
{
	HWND hWnd;
	MSG msg;

	// �E�B���h�E���쐬����
	hWnd = Create( hInst );
	if( hWnd == NULL )
	{
		MessageBox( NULL, _T("�E�B���h�E�̍쐬�Ɏ��s���܂���"), _T("�G���["), MB_OK );
		return 1;
	}

	// �E�B���h�E��\������
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );

	// ���b�Z�[�W���[�v
	while( 1 )
	{
		BOOL ret = GetMessage( &msg, NULL, 0, 0 );  // ���b�Z�[�W���擾����
		if( ret == 0 || ret == -1 )
		{
			// �A�v���P�[�V�������I�������郁�b�Z�[�W�����Ă�����A
			// ���邢�� GetMessage() �����s������( -1 ���Ԃ��ꂽ�� �j�A���[�v�𔲂���
			break;
		}
		else
		{
			// ���b�Z�[�W����������
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	return 0;
}

// �E�B���h�E���쐬����
HWND Create(HINSTANCE hInst)
{
	WNDCLASSEX wc;

	// �E�B���h�E�N���X�̏���ݒ�
	wc.cbSize = sizeof(wc);               // �\���̃T�C�Y
	wc.style = CS_HREDRAW | CS_VREDRAW;   // �X�^�C��
	wc.lpfnWndProc = WndProc;             // �E�B���h�E�v���V�[�W��
	wc.cbClsExtra = 0;                    // �g�����P
	wc.cbWndExtra = 0;                    // �g�����Q
	wc.hInstance = hInst;                 // �C���X�^���X�n���h��
	wc.hIcon = (HICON)LoadImage(          // �A�C�R��
		NULL, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON,
		0, 0, LR_DEFAULTSIZE | LR_SHARED
	);
	wc.hIconSm = wc.hIcon;                // �q�A�C�R��
	wc.hCursor = (HCURSOR)LoadImage(      // �}�E�X�J�[�\��
		NULL, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR,
		0, 0, LR_DEFAULTSIZE | LR_SHARED
	);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // �E�B���h�E�w�i
	wc.lpszMenuName = NULL;                     // ���j���[��
	wc.lpszClassName = _T("Default Class Name");// �E�B���h�E�N���X��
	
	// �E�B���h�E�N���X��o�^����
	if( RegisterClassEx( &wc ) == 0 ){ return NULL; }

	// �E�B���h�E���쐬����
	return CreateWindow(
		wc.lpszClassName,      // �E�B���h�E�N���X��
		_T("Sample Program"),  // �^�C�g���o�[�ɕ\�����镶����
		WS_OVERLAPPEDWINDOW,   // �E�B���h�E�̎��
		WINDOW_X,              // �E�B���h�E��\������ʒu�iX���W�j
		WINDOW_Y,              // �E�B���h�E��\������ʒu�iY���W�j
		WINDOW_WIDTH,          // �E�B���h�E�̕�
		WINDOW_HEIGHT,         // �E�B���h�E�̍���
		NULL,                  // �e�E�B���h�E�̃E�B���h�E�n���h��
		NULL,                  // ���j���[�n���h��
		hInst,                 // �C���X�^���X�n���h��
		NULL                   // ���̑��̍쐬�f�[�^
	);
}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	static LPCTSTR TEST_STR = _T("���{�^����������܂���");
	HDC hDC;
	HFONT hFont;
	static LOGFONT logfont;  // �t�H���g���̍\����
	

	switch( msg )
	{
	case WM_CREATE:			// �E�B���h�E���쐬���ꂽ�Ƃ�
		ZeroMemory( &logfont, sizeof(logfont) );  // �t�H���g���\���̂��O�ŏ�����
		logfont.lfUnderline = TRUE;           // ����������
		//logfont.lfCharSet = DEFAULT_CHARSET;  // �V�X�e���̃f�t�H���g�����Z�b�g���g��(Unicode?)
		logfont.lfCharSet = SHIFTJIS_CHARSET;//Shift-JIS 
		logfont.lfHeight=40;//����
		//strcpy( logfont.lfFaceName, "�l�r ����" );
		strcpy( logfont.lfFaceName, "�l�r �S�V�b�N" );


	case WM_LBUTTONDOWN:    // �}�E�X�̍��{�^���������ꂽ�Ƃ�
		hDC = GetDC( hWnd );
		//hFont = (HFONT)GetStockObject( ANSI_FIXED_FONT );  // �X�g�b�N�t�H���g���擾
		//SelectObject( hDC, hFont );
		
		hFont = CreateFontIndirect( &logfont );   // �_���t�H���g���쐬����
		SelectObject( hDC, hFont );
		TextOut( hDC, LOWORD( lp ), HIWORD( lp ), TEST_STR, (int)_tcslen(TEST_STR) );
		DeleteObject( hFont );   // �쐬�����_���t�H���g���폜����
		
		//TextOut( hDC, 50, 50, TEST_STR, (int)_tcslen(TEST_STR) );
		ReleaseDC( hWnd, hDC );
		return 0;

	case WM_DESTROY:        // �E�B���h�E���j�������Ƃ�
		PostQuitMessage( 0 );
		return 0;
	}

	return DefWindowProc( hWnd, msg, wp, lp );
}

