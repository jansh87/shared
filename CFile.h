#ifndef _CFILE_H
#define _CFILE_H
#include"TEntryList.h"
#include"TFile.h"
#include"TTree.h"

class CFile
{
	public:
		string FileName;
		string FriendFileName;
		string Name;
		string Tree;
		string Path;

		char Type;
		int HasFriend;

		TFile *File;
		TTree *tTree;
		TEntryList *EvtList;
		int fl_EvtList;

		float weight;

		CFile( const CFile& );
		~CFile();
		CFile(){};
		CFile(string );
		CFile(string,char);

		CFile(string, string);
		CFile(string, string, char);
		CFile(string,string,string, char);
		void Init(string path, string name, string tree, char type);
		void GetName();

};

#endif
