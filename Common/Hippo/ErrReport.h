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

void ReportErrWithLastErr(unsigned int dwError);
void ReportErrWithLastErr(unsigned int dwError,const char* str,...);
void ReportErr(const char* str,...);