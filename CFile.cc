#ifndef CFILE_CC
#define CFILE_CC

#include"CFile.h"
#include<iostream>
CFile::CFile (const CFile& B)
{
	FileName = B.FileName;
	FriendFileName = B.FriendFileName;
	Type = B.Type;
	HasFriend = B.HasFriend;
	Path = B.Path;
	Name = B.Name;
	Tree = B.Tree;

	fl_EvtList = B.fl_EvtList;
	weight = B.weight;
	
	tTree = B.tTree;

	if(!B.File) File = NULL;
	else File = new TFile(B.FileName.c_str(),"read");
	if(!B.EvtList) EvtList = NULL;
	else EvtList = new TEntryList(*B.EvtList);
	GetName();
}

CFile::~CFile()
{
	if(File){
		File->Close();
		delete File;
		File = NULL;
	}
	if(EvtList){
		delete EvtList;
		EvtList = NULL;
	}
	if(tTree){
		delete tTree;
		tTree = NULL;
	}
}

CFile::CFile(string file)
{
	FileName.assign(file);
	Type = 'm';
	HasFriend = 0;
	EvtList = NULL;
	fl_EvtList = 0;
	weight = 1.;
	File = NULL;
	tTree = NULL;

	GetName();
};

CFile::CFile(string file, char t)
{
	FileName.assign(file);
	HasFriend = 0;
	Type = t;
	EvtList = NULL;
	fl_EvtList = 0;
	weight = 1.;
	File = NULL;
	tTree = NULL;
	GetName();
};

CFile::CFile(string file, string afriend)
{
	FileName.assign(file);
	Type = 'm';
	FriendFileName.assign(afriend);
	HasFriend = 1;
	EvtList = NULL;
	fl_EvtList = 0;
	File = NULL;
	tTree = NULL;
	weight = 1.;
	GetName();
};

CFile::CFile(string file,  string afriend, char t)
{
	FileName.assign(file);
	FriendFileName.assign(afriend);
	HasFriend = 1;
	Type = t;
	EvtList = NULL;
	File = NULL;
	tTree = NULL;
	fl_EvtList = 0;
	weight = 1.;
	GetName();
};

CFile::CFile(string path,string name, string tree, char t)
{
    Init(path,name,tree,t);
};

void CFile::Init(string path,string name, string tree, char t)
{
    Path.assign(path);
    Name.assign(name);
    Tree.assign(tree);

    FileName.assign(Path+"/"+Name);
	HasFriend = 0;
	Type = t;
	EvtList = NULL;
	File = NULL;
	tTree = NULL;
	fl_EvtList = 0;
	weight = 1.;
}
void CFile::GetName()
{
	unsigned found = FileName.find_last_of("/");
	Name = FileName.substr(found+1,FileName.size()-7);
}
#endif
