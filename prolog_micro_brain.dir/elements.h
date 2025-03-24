// Brief translation of Elements.pas from AMALGAMA-project

#ifndef __ELEMENTS_H__
#define __ELEMENTS_H__

#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <map>
#include <list>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>
#include <cwctype>
#include <stdexcept>
#include <cwchar>

#include <string.h>

#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

#define infArity 32768

#define strClassIni L"Class.ini"
#define strScriptPHP L"Script.php3"
#define strDefinition L"Definition"
#define strParameters L"Parameters"
#define strName L"Name"
#define strInheritScript L"InheritScript"
#define strRequired L"Required"
#define strDirection L"Direction"
#define strType L"Type"
#define strLinks L"Links"
#define strInput L"Input"
#define strOutput L"Output"
#define strSingle L"Single"
#define strMany L"Many"

#define idfunGenerate L"Generate"
#define idfunPushCortege L"cortege_push"
#define idfunNextEvent L"NextEvent"

#define idlibAutoUtils L"autoutil.php3"
#define idlibUserVars L"_vars.php3"
#define idlibXPath L"XPath.class.php"
#define idParamsFile L"params.cfg"
#define idParamsOut L"params.out"
#ifdef __linux__
#define idParamsExe L"./lparams"
#else
#define idParamsExe L"params.exe"
#endif

#define idprmStage L"Stage"

#define idvarStage L"Stage"
#define idvarEvents L"Events"
#define idvarNumEvents L"NumEvents"
#define idvarTape L"Tape"

#define idconstResource L"stResource"
#define idconstInit L"stInit"
#define idconstCall L"stCall"
#define idconstDone L"stDone"

#define idfieldClassID L"ClassID"
#define idfieldID L"ID"

#define tagPHPOpen L"<?php"
#define tagPHPClose L"?>"

#define errPHP L"<#GENERROR>"
#define errMAIN L"!Error:"

const wstring ScriptPrepend = wstring(tagPHPOpen) + wstring(L"\r\n") +
wstring(L"include(\"") + wstring(idlibAutoUtils) + wstring(L"\");") + wstring(L"\r\n") +
wstring(L"include(\"") + wstring(idlibXPath) + wstring(L"\");") + wstring(L"\r\n") +
wstring(L"if (file_exists(\"") + wstring(idlibUserVars) + wstring(L"\"))") + wstring(L"\r\n") +
wstring(L"   include(\"") + wstring(idlibUserVars) + wstring(L"\");") + wstring(L"\r\n") +
wstring(L"\r\n") +
wstring(L"global $XML;") + wstring(L"\r\n") +
wstring(L"$xmlOptions = array(XML_OPTION_CASE_FOLDING => FALSE, XML_OPTION_SKIP_WHITE => TRUE);") + wstring(L"\r\n") +
wstring(L"$XML = new XPathEngine($xmlOptions);") + wstring(L"\r\n") +
wstring(L"$XML->importFromFile(\"_.xml\");") + wstring(L"\r\n");

const wstring ScriptPost = wstring(L"CloseAsserta();") + wstring(L"\r\n") +
wstring(L"fclose($MappedOutput);") + wstring(L"\r\n") +
wstring(L"ChangeOutput('stdout',true);") + wstring(L"\r\n") +
wstring(tagPHPClose);

wstring GenerateText(const wchar_t * src, int n, ...);
wstring ShiftRight(wstring S, int n);
wstring ReplaceAll(const wstring & src, const wstring & what, const wstring & to);

class TElementReg;
class TContactReg;
class TLinkReg;
class TObject;

// trim from start (in place)
inline void ltrim(std::wstring& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](wchar_t ch) {
		return !std::iswspace(ch);
		}));
}

// trim from end (in place)
inline void rtrim(std::wstring& s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](wchar_t ch) {
		return !std::iswspace(ch);
		}).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::wstring& s) {
	rtrim(s);
	ltrim(s);
}

wstring utf8_to_wstring(const string & str);
string wstring_to_utf8(const wstring& str);

template <class S>
bool bypass_spaces(const S & s, size_t & p) {
	do {
		while (p < s.length() && (s[p] == ' ' || s[p] == '\t' || s[p] == '\n' || s[p] == '\r'))
			p++;
		if (p < s.length() && s[p] == '%') {
			typename S::size_type lpos = s.find('\n', p);
			if (lpos == S::npos)
				p = s.length();
			else
				p = (size_t)(lpos + 1);
		}
		else
			break;
	} while (true);
	return p < s.length();
}

wstring get_complex(const wstring & s, size_t & p, wchar_t Before);

typedef std::function<void(const wstring &, const wstring &)> DescHandler;

void ProcessDesc(const vector<wstring> & Desc, DescHandler H);

typedef enum {
	dirInput = 1, dirOutput = 2
} TIODirection;

typedef enum {
	rsOk = 0, rsNonStrict, rsStrict
} TResultType;

const int flChecked = 0x01;
const int flClassesGenerated = 0x02;
const int flCallsGenerated = 0x04;
const int flPredicatesGenerated = 0x40;
const int flAllTemporary = flChecked | flClassesGenerated | flCallsGenerated | flPredicatesGenerated;

bool ElementIs(TElementReg * Ref, const wstring & IsClsID);
TElementReg * FindElementRegByID(const wstring & CID);
void GetContactsRegByClassID(const wstring & CID, TIODirection dir, vector<TContactReg *> & Contacts);

TElementReg * RegisterElement(const wstring & PCID,
	const wstring & CID,
	const vector<wstring> & Desc,
	const vector<wstring> & NewPrms,
	const wstring & Script);

TContactReg * RegisterContact(
	const wstring & clsID,
	const wstring & cntID,
	const vector<wstring> & Desc);

TLinkReg * RegisterLinkType(
	const wstring & clsID,
	const wstring & cntID,
	const wstring & Dsc
	);

void ClearAllRegistered();

bool LoadModellingDesktop(const wstring & parent, const wstring & root_dir);

bool NodeNameTester(char * NodeName, char * NodeTestString);

void * CreateSysF();
bool ExistClassF(const char * ClsID);
void * GetElementF(void * Sys, char * ID);
bool CanReachF(void * Sys, void *_From, int nTo, void **_To);
void CreateContactsF(char * ClassID, int _Dir, void * dom, void * Parent, char * Tag);
void * AddElementF(void * Sys, char * ClassName, char * ID, int Flags);
void * AddLinkF(void * Sys, void * El, char * ContID, void * PEl, char * PContID, char ** S, bool Info);
bool AnalyzeLinkStatusIsInformF(void * sys, void * L);
void SetParameterIfExistsF(void * el, char * PrmName, char * PrmValue);
void MoveF(void * el, int X, int Y);
int CheckSysF(void * Sys);
void ToStringF(void * Sys, char * Ret);
void GenerateCodeF(void * Sys, char * Ret);
void SaveToXMLF(void * Sys, char * FName);
void _FreeF(void * Obj);

typedef void * (*CreateSysFun)();
typedef bool(*ExistClassFun)(const char * ClsID);
typedef void * (*GetElementFun)(void * Sys, char * ID);
typedef bool(*CanReachFun)(void * Sys, void * _From, int nTo, void ** _To);
typedef void (*CreateContactsFun)(char * ClassID, int _Dir, void * dom, void * Parent, char * Tag);
typedef void * (*AddElementFun)(void * Sys, char * ClassName, char * ID, int Flags);
typedef void * (*AddLinkFun)(void * Sys, void * El, char * ContID, void * PEl, char * PContID, char ** S, bool Info);
typedef bool (*AnalyzeLinkStatusIsInformFun)(void * sys, void * L);
typedef void (*SetParameterIfExistsFun)(void * el, char * PrmName, char * PrmValue);
typedef void (*MoveFun)(void * el, int X, int Y);
typedef int (*CheckSysFun)(void * Sys);
typedef void (*ToStringFun)(void * Sys, char * Ret);
typedef void (*GenerateCodeFun)(void * Sys, char * Ret);
typedef void (*SaveToXMLFun)(void * Sys, char * FName);
typedef void (*_FreeFun)(void * Obj);
typedef bool(*TXPathNodeNameTester)(char * NodeName, char * NodeTestString);

typedef bool (* XPathInductF) (
	bool _Messaging,
	CreateSysFun CreateSysF,
	ExistClassFun ExistClassF,
	GetElementFun GetElementF,
	CanReachFun CanReachF,
	CreateContactsFun CreateContactsF,
	AddElementFun AddElementF,
	AddLinkFun AddLinkF,
	AnalyzeLinkStatusIsInformFun AnalyzeLinkStatusIsInformF,
	SetParameterIfExistsFun SetParameterIfExistsF,
	MoveFun MoveF,
	CheckSysFun CheckSysF,
	ToStringFun ToStringF,
	GenerateCodeFun GenerateCodeF,
	SaveToXMLFun SaveToXMLF,
	_FreeFun _FreeF,
	TXPathNodeNameTester NodeNameTesterF,
	const char * SelectedMode,
	bool UseNNet,
	bool MainLineAllowed,
	void * _ENV,
	const char * inENV, char * outENV,
	const char * InXML, const char * OutXML,
	int MaxCPUs,
	const char * _IDs,
	bool OnlyInduceModel);
extern XPathInductF XPathInduct;

typedef bool(*CompileXPathingF)(
	bool _Messaging,
	const char * _AllowedVersions,
	const char * FName,
	void *_ENV,
	const char * inENV, const char * outENV,
	char * _WorkText);
extern CompileXPathingF CompileXPathing;

typedef void (*SetIntervalF)(uint32_t _Interval);
extern SetIntervalF SetInterval;

typedef void (*ClearRestrictionsF)();
extern ClearRestrictionsF ClearRestrictions;

typedef void (*ClearRulerF)();
extern ClearRulerF ClearRuler;

typedef void (*SetDeduceLogFileF)(const char * LF);
extern SetDeduceLogFileF SetDeduceLogFile;

typedef void (*CreateDOMContactF)(void * dom, void * Parent, char * Tag, const char * CntID);
extern CreateDOMContactF CreateDOMContact;

typedef wchar_t (*GetMSGF)();
extern GetMSGF GetMSG;

typedef struct TParameter {
	wstring Name;
	wstring DefValue;
	TElementReg * Definer = NULL;
	bool Redefined = false;
} TParameter;

class TLinkReg {
public:
	wstring OutClsID;
	wstring OutContID;
	wstring InClsID;
	wstring InContID;
public:
	TLinkReg(
		const wstring & outClsID,
		const wstring & outContID,
		const wstring & Desc) : OutClsID(outClsID), OutContID(outContID) {
			wstring::size_type spos = Desc.find('\\');
			if (spos == wstring::npos)
				throw logic_error("No \\ in Link description");
			InClsID = Desc.substr(0, spos);
			InContID = Desc.substr(spos + 1);
	}
};

class TContactReg {
public:
	wstring ClsID;
	wstring CntID;
	wstring Name;
	TIODirection Dir;
	bool Required;
	int MaxArity;
public:
	TContactReg(const wstring & clsID, const wstring & cntID,
		const vector<wstring> & Desc) :
		ClsID(clsID), CntID(cntID)
	{
		Name = L"";
		Dir = dirInput;
		Required = false;
		MaxArity = infArity;
		ProcessDesc(Desc,
			[this](const wstring & Nm, const wstring & Val) {
			if (Nm == strName) this->Name = Val;
			else if (Nm == strDirection)
				if (Val == strInput) this->Dir = dirInput;
				else if (Val == strOutput) this->Dir = dirOutput;
				else
					throw logic_error("Unknown Link Direction!");
			else if (Nm == strRequired)
				if (Val == "1") this->Required = true;
				else if (Val == "0") this->Required = false;
				else
					throw logic_error("Malformed Required of contact");
			else if (Nm == strType)
				if (Val == strSingle) this->MaxArity = 1;
				else if (Val == strMany) this->MaxArity = infArity;
				else
					throw logic_error("Unknown Link Type");
			else if (Nm == strLinks) {
				wchar_t links[1024];
				wcsncpy(links, Val.c_str(), sizeof(links)/sizeof(wchar_t) - 1);
				links[1023] = 0;
				wchar_t * ptr = NULL;
				wchar_t * link = std::wcstok(links, L" ;\t", &ptr);
				while (link) {
					RegisterLinkType(this->ClsID, this->CntID, wstring(link));
					link = std::wcstok(NULL, L" ;\t", &ptr);
				}
			}
		});
	}
};

class TElementReg {
private:
	bool FUsed;
public:
	TElementReg * Parent;
	wstring ClsID;
	wstring Name;
	bool Inherit;
	bool Generated;
	wstring Script;
	multimap<wstring, TParameter *> Params;
public:
	TElementReg(
		const wstring & PCID,
		const wstring & CID,
		const vector<wstring> & Desc,
		const vector<wstring> & NewPrms,
		const wstring & script) : ClsID(CID), Script(script) {

		Generated = false;
		FUsed = false;
		Inherit = false;
		Name = L"";

		auto CreateParams = [&](TElementReg * Prnt) {
			multimap<wstring, TParameter *> PrntParams;
			if (Prnt)
				Prnt->CollectParams(PrntParams);
			ProcessDesc(Desc,
				[this](const wstring & Nm, const wstring & Val) {
					if (Nm == strName) this->Name = Val;
					else if (Nm == strInheritScript)
						if (Val == "1") this->Inherit = true;
			});
			for (const wstring & Prm : NewPrms) {
				size_t p = 0;
				bypass_spaces(Prm, p);
				if (p < Prm.length()) {
					if (Prm[p] == '{') {
						p++;
						get_complex(Prm, p, '}');
						p++;
					}
					if (p < Prm.length()) {
						wstring::size_type epos = Prm.find('=', p);
						TParameter * newp = new TParameter;
						if (epos != wstring::npos) {
							newp->Name = Prm.substr(p, epos - p);
							newp->DefValue = Prm.substr(epos + 1);
						}
						else {
							newp->Name = Prm.substr(p);
							newp->DefValue = L"";
						}
						trim(newp->Name);
						trim(newp->DefValue);
						newp->Definer = this;
						newp->Redefined = false;
						Params.insert(pair<wstring, TParameter *>(newp->Name, newp));
					}
				}
			}
			multimap<wstring, TParameter *>::iterator itp;
			for (itp = PrntParams.begin(); itp != PrntParams.end(); itp++) {
				multimap<wstring, TParameter *>::iterator itt = Params.find(itp->first);
				if (itt != Params.end()) {
					itt->second->Definer = itp->second->Definer;
					itt->second->Redefined = true;
				}
			}
		};

		if (PCID.length() == 0) {
			Parent = NULL;
			CreateParams(NULL);
		}
		else {
			Parent = FindElementRegByID(PCID);
			if (Parent)
				CreateParams(Parent);
			else
				throw logic_error("Unknown class");
		}
	}
	bool getUsed() const { return FUsed; }
	void setUsed(bool Value) {
		FUsed = Value;
		if (Value && Inherit && Parent)
			Parent->setUsed(true);
	}
	virtual void CollectParams(multimap<wstring, TParameter *> & Prms) {
		if (Parent)
			Parent->CollectParams(Prms);
		Prms.insert(Params.begin(), Params.end());
	}
	virtual bool ProducePrms(bool Prolog, wstring & Code,
		TIODirection _Dir, const wstring & Prepend, const bool DummyPrologVars = false);
	virtual bool GeneratePHP(wstring & Code);
	virtual ~TElementReg() {
		multimap<wstring, TParameter *>::iterator it = Params.begin();
		while (it != Params.end()) {
			delete it->second;
			it++;
		}
	}
};

class TObject {
public:
	TObject() { }
	virtual ~TObject() { }
};

class TElement;
class TLink;
class TSystem;

class TContact : public TObject {
public:
	wstring Name; // Отображаемое имя
	TElement * Owner;
	vector<TLink *> Links;
	TContactReg * Ref;
public:
	TContact(const wstring & Nm, TElement * Own, TContactReg * _Ref) :
		Name(Nm), Owner(Own), Ref(_Ref) { }
	virtual ~TContact();
};

class TLink : public TObject {
public:
	TContact * _From;
	TContact * _To;
	bool Inform;
public:
	TLink(TContact * __From, TContact * __To, bool _Inform) :
		_From(__From), _To(__To), Inform(_Inform) { }
	virtual ~TLink() {
		_From->Links.erase(find(_From->Links.begin(), _From->Links.end(), this));
		_To->Links.erase(find(_To->Links.begin(), _To->Links.end(), this));
	}
};

class TElement : public TObject {
public:
	wstring Ident; // Идентификатор в GEN - программе
	TElementReg * Ref;
	map<wstring, TContact *> Inputs;
	map<wstring, TContact *> Outputs;
	map<wstring, wstring> Parameters;
	map<wstring, TParameter *> ParameterObjs;
	int Flags;
	int X, Y;
public:
	TElement() : Flags(0), Ref(NULL), X(0), Y(0) { }
	TElement(TElementReg * _Ref, const wstring & ID, int Flgs);
	void Move(int x, int y);
	TContact * AddContact(const wstring & ID, const wstring & Name,
		TContactReg * _Ref);
	virtual void ClearFlags(int ClearMask) {
		Flags &= ~ClearMask;
	}
	virtual void SetFlags(int SetMask) {
		Flags |= SetMask;
	}
	virtual int Check();
	virtual wstring ToString();
	virtual bool GenerateClasses(wstring & Parameter);
	virtual bool GenerateCalls(wstring & Parameter);
	void FindConnectedByType(const wstring & ClsID,
		TIODirection Dir,
		vector<TElement *> & objs) const;
	virtual ~TElement();
};

class TSystem : public TElement {
public:
	map<wstring, TElement *> Elements;
public:
	TSystem() { }
	virtual ~TSystem() {
		map<wstring, TElement *>::iterator ite;
		for (ite = Elements.begin(); ite != Elements.end(); ite++)
			delete ite->second;
	}
	virtual void ClearFlags(int ClearMask) {
		map<wstring, TElement *>::iterator ite;
		for (ite = Elements.begin(); ite != Elements.end(); ite++)
			ite->second->ClearFlags(ClearMask);
	}
	virtual void SetFlags(int SetMask) {
		map<wstring, TElement *>::iterator ite;
		for (ite = Elements.begin(); ite != Elements.end(); ite++)
			ite->second->SetFlags(SetMask);
	}
	virtual int Check();
	virtual wstring ToString();
	void EnumerateObjs(std::function<void(TElement *)> fun) {
		map<wstring, TElement *>::iterator it = Elements.begin();
		while (it != Elements.end()) {
			fun(it->second);
			it++;
		}
	}
	void EnumerateLinks(std::function<void(TLink *)> fun) {
		map<wstring, TElement *>::iterator it = Elements.begin();
		while (it != Elements.end()) {
			map<wstring, TContact *>::iterator itc = it->second->Outputs.begin();
			while (itc != it->second->Outputs.end()) {
				for (TLink * L : itc->second->Links)
					fun(L);
				itc++;
			}
			it++;
		}
	}
	virtual bool GeneratePHP(wstring & Parameter);
	virtual bool GenerateClasses(wstring & Parameter) {
		throw logic_error("TSystem.GenerateClasses() not exists!");
	}
	virtual bool GenerateCalls(wstring & Parameter) {
		throw logic_error("TSystem.GenerateCalls() not exists!");
	}
	void AnalyzeLinkStatus(TLink * L);
	bool Cycled(vector<TElement *> & ObjList, TElement * Obj, TElement * LinkedObj);
	int Cascade(TElement * Obj, int Flag, wstring & Parameter);
	int MakeCascade(int Flag, wstring & Parameter);
	bool Reach(TElement * _From, int nTo, void ** _To);
	TElement * GetElement(const wstring & ID);
	TElement * AddElement(const wstring & CID, const wstring & ID, int Flgs);
	TLink * AddLink(TContact * _From, TContact * _To, bool Inf = false);
	bool LoadFromXML(wstring & Lang, const wstring & inFileName);
	void SaveToXML(const wstring & outFileName);
};

#endif
