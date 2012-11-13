
// pNju3Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CpNju3Dlg 对话框
class CpNju3Dlg : public CDialogEx
{
// 构造
public:
	CpNju3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PNJU3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
