
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
	CString localFilePath;
	static BOOL CreatedMultipleDirectory(wchar_t* direct);
	static BOOL FolderExist(CString& strPath);
	CString GetLocalFilePath();
	BOOL HTTPGetFile(CString URLStr, CString strLocalSavePath);
	BOOL unCompressFile(CString *mZipFileFullPath);
	BOOL downFlag;
	int flag;
	HANDLE m_ThreadDownload;
	HANDLE m_ThreadUnCompress;
// 对话框数据
	enum { IDD = IDD_FTNNHTTPLOGHELPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual void OnOK();

	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	
	afx_msg void OnPaint();
	afx_msg void OnBnClickedDownload();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeUrledit();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStaitc();
	afx_msg void OnStnClickedDowntext();
};
