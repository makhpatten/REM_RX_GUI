#include "afxcmn.h"
#include "afxwin.h"
#include "cdxCRotBevelLine.h"

class CChannelsDlg : public CDialog
{
public:
	CChannelsDlg(CWnd*);

// Dialog Data
	//{{AFX_DATA(CScanDlg)
	enum { IDD = IDD_CHANNELSWINDOW };
	//}}AFX_DATA

public:
	CStatic m_newerArea;
//	int mhpxxx;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScanDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClose();


	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CScanDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedChannelsOk();
//	void getStartStopStepFreqs();
//	void drawGraphTrace();
//	CDC *channelsscanDrawingContext;
//	static void UpdateChannelIndicatorLights();

//	void setIndicatorLight(int, int);

public:
//	CEdit m_startFreqTxt;
//	CEdit m_stopFreqTxt;
//	CEdit m_stepFreqTxt;
//	ULONG startFreqKHz;
//	ULONG stopFreqKHz;
//	ULONG stepFreqKHz;

//public:
//	afx_msg void OnBnClickedDrawLines();
public:
	afx_msg void OnBnClickedChannelsClose();
public:
/*		CProgressCtrl m_Channels_Level1;
	CProgressCtrl m_Channels_Level2;
	CProgressCtrl m_Channels_Level3;
	CProgressCtrl m_Channels_Level4;
	CProgressCtrl m_Channels_Level5;
	CProgressCtrl m_Channels_Level6;
	CProgressCtrl m_Channels_Level7;
	CProgressCtrl m_Channels_Level8;
*/

public:
	cdxCRotBevelLine m_freqLabel1;
//public:
//	CListBox m_tuneFreqText;
};


