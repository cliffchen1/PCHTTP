
// FTNNHTTPLogHelperDlg.h : 头文件
//

#pragma once


// CFTNNHTTPLogHelperDlg 对话框
class CFTNNHTTPLogHelperDlg : public CDialogEx
{
// 构造
public:
	CFTNNHTTPLogHelperDlg(CWnd* pParent = NULL);	// 标准构造函数
	BOOL flag_UnCompress;
	static CString localFilePath;
	static BOOL CreatedMultipleDirectory(wchar_t* direct);
	static BOOL FolderExist(CString& strPath);
	CString GetLocalFilePath();
	static DWORD WINAPI HTTPGetFile(LPVOID lpParameter);
	BOOL unCompressFile(CString *mZipFileFullPath);
	BOOL downFlag;
	
	HANDLE m_ThreadDownload;
// 对话框数据
	enum { IDD = IDD_FTNNHTTPLOGHELPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedDownload();
	afx_msg LRESULT OnUserLogin(WPARAM wParam, LPARAM lParam);
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeUrledit();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaitc();
};
