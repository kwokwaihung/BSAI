// This is a part of the IVCS Project
// Copyright (C) 2006 The Hong Kong Polytechnic University
// All rights reserved.
//
//------------------------------------------------------------------------------
// Title            : Display image on popup window
//
// Class Name       : CWindowDisplay
// File Name        : WindowDisplay.h
// Module Leader    : Prof. W.C. Siu
// Programmer       : HUI Wai Lam
// Class Version    : 1.12
// Date             : 8 Sept 2006
//
// DESC.            : Display image on popup window
//------------------------------------------------------------------------------

#if !defined(AFX_WINDOWDISPLAY_H__4072EBAF_ADE4_4174_8B60_8DCBD2F1DD3B__INCLUDED_)
#define AFX_WINDOWDISPLAY_H__4072EBAF_ADE4_4174_8B60_8DCBD2F1DD3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <vfw.h>



class CWindowDisplay  
{
public:
    enum {  
        nMaxWindow = 16         //!< Maximum window supported
    } MaxWindow;

    enum {  
        VIDEO_BEGIN			= (WM_USER + 0),        //!< Begin draw bitmap message
        VIDEO_DRAW_FRAME	= (WM_USER + 1),        //!< Draw bitmap message
        VIDEO_REDRAW_FRAME	= (WM_USER + 2),        //!< Redraw bitmap message
        VIDEO_END			= (WM_USER + 3)         //!< End draw bitmap message
    } UserMessage;

public:
	CWindowDisplay();                       //!< default constructor
	virtual ~CWindowDisplay();              //!< default destructor

	bool        Init(int nWidth, int nHeight, char *szWinTitle);            // Initialize display module
	void        CloseWindow(void);

  void        SetWindowTitle(char *szWinTitle);                           // Set Window Title
	void        SetWindowPos(int nLeft, int nTop);                          // Set window placement position

  bool        LoadDib(LPCTSTR lpszFileName);                              // Load DIB from file
	bool        LoadDib(BYTE *pBitmapBuffer, DWORD dwLength);               // Load DIB from memory buffer
	bool        LoadDib(BYTE *pRGBBuffer, int nWidth, int nHeight);         // Load raw bitmap from memory
	bool        LoadYUV420(BYTE *pYUV420, int nWidth, int nHeight);         // Load a raw YUV 4:2:0 image from memory
	bool        LoadYUV420(char *szFileName, int nWidth, int nHeight);      // Load a raw YUV 4:2:0 image from file
	bool        LoadYUV420File(char *szFileName, int nWidth, int nHeight);  // Load a raw YUV 4:2:0 image from file
  bool        LoadGray(BYTE *pImage, int nWidth, int nHeight);            // Load a gray image from memory
  bool        LoadGray(char *szFileName, int nWidth, int nHeight);        // Load a gray image from file
  bool        SaveDib(LPCTSTR lpszFileName);                              // Save DIB to file

	BYTE        *GetRGBBuffer(void);                    // Return RGB 24-bit image buffer
	BYTE        *GetYUV420Buffer(void);                 // Return YUV 420 image buffer
	int         GetWidth(void);                         // Return width of the image
	int         GetHeight(void);                        // Return height of the image

    HWND        GetHWND(void);                          // Return window handle

private:
    bool    InitDisplayThread(void);            // Startup display thread
	void    WinMain(void);                      // Display window WinMain
	static void DisplayWinMain(void *pParam);   // Display window WinMain ThreadProc
    void    MainWndProc1(HWND hWnd, UINT msg, UINT wParam, LONG lParam);
    static LRESULT APIENTRY MainWndProc (HWND hWnd, UINT msg, UINT wParam, LONG lParam);

	void    Free(void);
    int     DrawDIB(void);                  // Draw DIB onto window
	void    OnBeginDraw(HWND hWnd);
	void    OnEndDraw(HWND hWnd);
	void    DrawFrame(HWND hWnd);

	bool    ReadBitmap(char *szFileName);           // Load RGB-24 bit image
  bool    WriteBitmap(char *szFileName);          // Save RGB-24 bit image

protected:
    int         m_nExtraWidth;              //!< Winodw extra width for window boarder
    int         m_nExtraHeight;             //!< Window extra height for window boarder and caption bar
    int         m_nLeftPos;                 //!< Window initial Left position
    int         m_nTopPos;                  //!< Window initial top position
    HWND        m_hDisplayWnd;              //!< Display window handle
    HDC         m_hDC;                      //!< main window display DC
	HANDLE      m_hDisplayThread;           //!< Display window thread handle
	DWORD       m_dwThreadID;               //!< Display thread ID
	HANDLE      m_hEventMain;               //!< Main event
	HANDLE      m_hEventDisplay;            //!< Display synchronization thread
    WNDCLASS    m_wc;                       //!< Window Class
    char        m_szWinTitle[200];          //!< Window Title Name
    int         m_nWidth;                   //!< Window width
    int         m_nHeight;                  //!< Window height

    RECT        m_rect;                     //!< drawing region of the window
    HDRAWDIB    m_hDrawDib;                 //!< handle for drawing the bitmap
    BITMAPINFOHEADER m_biHeader;            //!< bitmap header
    BYTE        *m_pRGB;                    //!< pointer to the RGB buffer
    BYTE        *m_pYUV420;                 //!< pointer to the YUV420 buffer
    bool        m_bRGB;                     //!< Flag to indicate the image inside RGB buffer is valid
    bool        m_bYUV420;                  //!< Flag to indicate the image inside YUV420 buffer is valid
    bool        m_bImageIsReady;            //!< Flag to indicate the image in the RGB buffer is ready to be paint

    int         m_nWindowIndex;             //!< Index to the global window list

protected:
	virtual void    OnSize(HWND hWnd, UINT wParam, LONG lParam);
	virtual void    OnPaint(HWND hWnd, UINT wParam, LONG lParam);
	virtual void    OnDestroyWindow(HWND hWnd, UINT wParam, LONG lParam);
	virtual void    OnCreate(HWND hWnd, UINT wParam, LONG lParam);
};

//! Window List structure
typedef struct SWindowList {
    CWindowDisplay  *pWD;       //!< class pointer
    HWND            hWnd;       //!< window handle
} SWindowList;

static  SWindowList g_WindowList[CWindowDisplay::nMaxWindow];       //!< Global Window List
static  int         g_nTotalWindow=0;                 //!< Total window in list

CWindowDisplay *MapHandle2Ptr(HWND hWnd);       //!< Map the window handle to class pointer

#endif // !defined(AFX_WINDOWDISPLAY_H__4072EBAF_ADE4_4174_8B60_8DCBD2F1DD3B__INCLUDED_)
