
// pNju3Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CpNju3Dlg �Ի���
class CpNju3Dlg : public CDialogEx
{
// ����
public:
	CpNju3Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PNJU3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	int GetVerifyPng(char* filepath);
	void GetPng(char* filepath, int* PngData);
	CString Verify(char* VerifyPath);
	int FillEdit(void);
	void Connect(CString UserID, CString Password, CString VerifyCode);
	CEdit m_UserID;
public:
	CEdit m_Password;
private:
	CEdit m_VerifyCode;
public:
	afx_msg void OnBnClickedOk();
	void SaveUserIDPassword(CString UserID, CString Password);
private:
	void ReadUserIDPassword(CString& UserID, CString& Password);
};
