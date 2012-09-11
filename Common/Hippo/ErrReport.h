/********************************************************************
	created:	2011/10/19
	created:	19:10:2011   23:31
	filename: 	f:\TestHippo\TestHippo\HIPPO_FrameWork\ErrReport.h
	file path:	f:\TestHippo\TestHippo\HIPPO_FrameWork
	file base:	ErrReport
	file ext:	h
	author:		sssa2000
	
	purpose:	
*********************************************************************/
#pragma once

void HippoReportErrWithLastErr(unsigned int dwError);
void HippoReportErrWithLastErr(unsigned int dwError,const char* str,...);
void HippoReportErr(const char* str,...);