
// FTNNHTTPLogHelperDlg.h : ͷ�ļ�
//

#pragma once


// CFTNNHTTPLogHelperDlg �Ի���
class CFTNNHTTPLogHelperDlg : public CDialogEx
{
// ����
public:
	CFTNNHTTPLogHelperDlg(CWnd* pParent = NULL);	// ��׼���캯��
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
// �Ի�������
	enum { IDD = IDD_FTNNHTTPLOGHELPER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	virtual void OnOK();

	
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
