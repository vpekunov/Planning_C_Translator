#include "elements.h"
#include <stdio.h>
#include <cwctype>
#include <functional>
#include <fstream>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <cstdarg>

using namespace std;

#include "tinyxml2.h"

using namespace tinyxml2;

map<wstring, TElementReg *> ElementRegList;
multimap<wstring, TContactReg *> ContactRegList;
multimap<wstring, TLinkReg *> LinkRegList;

XPathInductF XPathInduct = NULL;
CompileXPathingF CompileXPathing = NULL;
SetIntervalF SetInterval = NULL;
ClearRestrictionsF ClearRestrictions = NULL;
ClearRulerF ClearRuler = NULL;
SetDeduceLogFileF SetDeduceLogFile = NULL;
CreateDOMContactF CreateDOMContact = NULL;
GetMSGF GetMSG = NULL;

// trim from start (in place)
inline void ltrim(std::wstring &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](wchar_t ch) {
		return !std::iswspace(ch);
	}));
}

// trim from end (in place)
inline void rtrim(std::wstring &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](wchar_t ch) {
		return !std::iswspace(ch);
	}).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::wstring &s) {
	rtrim(s);
	ltrim(s);
}

wstring utf8_to_wstring(const string & str)
{
//	wstring_convert<codecvt_utf8_utf16<wchar_t> > myconv;
//	return myconv.from_bytes(str);
	return wstring(str.begin(), str.end());
}

string wstring_to_utf8(const wstring& str)
{
//	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
//	return myconv.to_bytes(str);
	return string(str.begin(), str.end());
}

wstring ReplaceAll(const wstring & src, const wstring & what, const wstring & to) {
	wstring result = src;
	wstring::size_type n = 0;
	while ((n = result.find(what, n)) != wstring::npos)
	{
		result.replace(n, what.size(), to);
		n += to.size();
	}
	return result;
}

wstring GenerateText(const wchar_t * src, int n, ...) {
	va_list args;
	va_start(args, n);

	wstring result = src;
	for (int i = 0; i < n; i++) {
		wstring arg = wstring(va_arg(args, wchar_t *));
		char buf[100];
		sprintf(buf, "$[%i]", i);
		result = ReplaceAll(result, utf8_to_wstring(buf), arg);
	}

	va_end(args);
	return result;
}

wstring ShiftRight(wstring S, int n) {
	auto Count = [&](wstring & S, const wstring & FindStr)->int {
		int Result = 0;
		wstring::size_type P;
		do {
			P = S.find(FindStr);
			if (P != wstring::npos) {
				Result++;
				S.erase(S.begin() + P, S.begin() + P + FindStr.length());
			}
		} while (P != wstring::npos);
		return Result;
	};

	int PHPBal, PHPBalOld;
	wstring Result = L"";
	wstring Sh = wstring(n, ' ');
	PHPBal = 1;
	while (S.length()) {
		wstring::size_type P = S.find(L"\r\n");
		if (P == wstring::npos) P = 32768*32;
		wstring Cur = S.substr(0, P + 2);
		PHPBalOld = PHPBal;
		PHPBal += Count(Cur, tagPHPOpen) - Count(Cur, tagPHPClose);
		if (PHPBalOld == 0 && PHPBal >= 0)
			Result += S.substr(0, P + 2);
		else
			Result += Sh + S.substr(0, P + 2);
		S.erase(S.begin(), S.begin() + P + 2);
	}
	return Result;
}

wstring get_complex(const wstring & s, int & p, wchar_t Before) {
	wchar_t quote = 0x0;
	wstring str;
	bypass_spaces(s, p);
	while (p < s.length() && s[p] != Before) {
		str += s[p];
		if (quote) {
			if (s[p] == quote)
				quote = 0x0;
		}
		else if (s[p] == '\'' || s[p] == '"') {
			quote = s[p];
		}
		else if (s[p] == '(') {
			p++;
			str += get_complex(s, p, ')');
			if (p < s.length()) str += s[p];
		}
		else if (s[p] == '[') {
			p++;
			str += get_complex(s, p, ']');
			if (p < s.length()) str += s[p];
		}
		else if (s[p] == '{') {
			p++;
			str += get_complex(s, p, '}');
			if (p < s.length()) str += s[p];
		}
		p++;
	}
	if (quote || p >= s.length())
		return L"";
	else
		return str;
}

void ProcessDesc(const vector<wstring> & Desc, DescHandler H) {
	for (const wstring & Dsc : Desc) {
		int p = 0;
		bypass_spaces(Dsc, p);
		if (p < Dsc.length()) {
			wstring::size_type epos = Dsc.find('=', p);
			wstring Nm, Val;
			if (epos != wstring::npos) {
				Nm = Dsc.substr(p, epos - p);
				Val = Dsc.substr(epos + 1);
			}
			else {
				Nm = Dsc.substr(p);
				Val = L"";
			}
			trim(Nm);
			trim(Val);
			H(Nm, Val);
		}
	}
}

bool ElementIs(TElementReg * Ref, const wstring & IsClsID) {
	bool Result = false;
	while (Ref && !Result)
	if (Ref->ClsID == IsClsID)
		Result = true;
	else
		Ref = Ref->Parent;
	return Result;
}

TElementReg * FindElementRegByID(const wstring & CID) {
	map<wstring, TElementReg *>::iterator it = ElementRegList.find(CID);
	if (it == ElementRegList.end())
		return NULL;
	else
		return it->second;
}

void GetContactsRegByClassID(const wstring & CID, TIODirection dir, vector<TContactReg *> & Contacts) {
	TElementReg * Ref = FindElementRegByID(CID);
	Contacts.clear();
	if (Ref == NULL) return;
	multimap<wstring, TContactReg *>::iterator itc;
	for (itc = ContactRegList.begin(); itc != ContactRegList.end(); itc++) {
		if (itc->second->Dir == dir && ElementIs(Ref, itc->second->ClsID)) {
			Contacts.push_back(itc->second);
		}
	}
}

TElementReg * RegisterElement(const wstring & PCID,
	const wstring & CID,
	const vector<wstring> & Desc,
	const vector<wstring> & NewPrms,
	const wstring & Script) {
	TElementReg * result = new TElementReg(PCID, CID, Desc, NewPrms, Script);
	ElementRegList.insert(pair<wstring, TElementReg *>(
		CID,
		result
		));
	return result;
}

TContactReg * RegisterContact(
	const wstring & clsID,
	const wstring & cntID,
	const vector<wstring> & Desc) {
	TContactReg * result = new TContactReg(clsID, cntID, Desc);
	ContactRegList.insert(pair<wstring, TContactReg *>(
		clsID,
		result
		));
	return result;
}

TLinkReg * RegisterLinkType(
	const wstring & clsID,
	const wstring & cntID,
	const wstring & Dsc
	) {
	TLinkReg * result = new TLinkReg(clsID, cntID, Dsc);
	LinkRegList.insert(pair<wstring, TLinkReg *>(
		clsID,
		result
		));
	return result;
}

void ClearAllRegistered() {
	map<wstring, TElementReg *>::iterator it = ElementRegList.begin();
	while (it != ElementRegList.end()) {
		delete it->second;
		it++;
	}
	ElementRegList.clear();
	multimap<wstring, TContactReg *>::iterator itc = ContactRegList.begin();
	while (itc != ContactRegList.end()) {
		delete itc->second;
		itc++;
	}
	ContactRegList.clear();
	multimap<wstring, TLinkReg *>::iterator itl = LinkRegList.begin();
	while (itl != LinkRegList.end()) {
		delete itl->second;
		itl++;
	}
	LinkRegList.clear();
}

bool LoadModellingDesktop(const wstring & parent, const wstring & root_dir) {
	if (is_directory(root_dir)) {
		try {
			// Handle ini-file
			wpath p(root_dir);
			wstring fname = root_dir;
			wstring fsname = root_dir;
			fname += L"/";
			fsname += L"/";
			fname += strClassIni;
			fsname += strScriptPHP;
			if (p.filename().string().substr(0, 3) != "cls")
				p = "";
			std::ifstream IN(wstring_to_utf8(fname));
			if (IN) {
				map <wstring, vector<wstring>> sections;
				wstring section;
				string _line;
				wstring line;
				while (getline(IN, _line)) {
					line = utf8_to_wstring(_line);
					trim(line);
					if (line.length() > 2) {
						if (line[0] == '[') {
							wstring::size_type pos = line.find(']');
							if (pos != wstring::npos) {
								section = line.substr(1, pos - 1);
								sections[section] = vector<wstring>();
							}
							else
								throw logic_error("No ending ']'");
						}
						else if (!section.empty()) {
							sections[section].push_back(line);
						}
						else
							throw logic_error("No first [...]");
					}
				}
				IN.close();
				std::ifstream INS(wstring_to_utf8(fsname));
				wstring script = L"";
				if (INS) {
					string _line;
					wstring line;
					while (getline(INS, _line)) {
						line = utf8_to_wstring(_line);
						script += line;
						script += L"\r\n";
					}
					if (script.substr(0, wstring(tagPHPOpen).length()) != wstring(tagPHPOpen))
						script = wstring(tagPHPOpen) + wstring(L"\r\n") + script;
					if (script.substr(script.length() - wstring(tagPHPClose).length() - 2) != wstring(tagPHPClose) + wstring(L"\r\n"))
						script += wstring(L"\r\n") + wstring(tagPHPClose) + wstring(L"\r\n");
					INS.close();
				}
				map <wstring, vector<wstring>>::iterator itd = sections.find(strDefinition);
				map <wstring, vector<wstring>>::iterator itp = sections.find(strParameters);
				if (itd != sections.end() && itp != sections.end()) {
					vector<wstring> definition = itd->second;
					vector<wstring> parameters = itp->second;
					sections.erase(itd);
					sections.erase(sections.find(strParameters));
					RegisterElement(parent, p.filename().wstring(), definition, parameters, script);
					map <wstring, vector<wstring>>::iterator itc = sections.begin();
					while (itc != sections.end()) {
						RegisterContact(p.filename().wstring(), itc->first, itc->second);
						itc++;
					}
				}
				else
					throw logic_error("No [Definition] or [Parameters]");
			}
			for (directory_iterator it(root_dir), eit; it != eit; ++it) {
				if (is_directory(it->path())) {
					LoadModellingDesktop(p.filename().wstring(), it->path().wstring());
				}
			}
		}
		catch (...) {
			return false;
		}
		return true;
	}
	else
		return false;
}

bool TElementReg::ProducePrms(bool Prolog, wstring & Code,
	TIODirection _Dir, const wstring & Prepend, const bool DummyPrologVars) {
	bool Result = false;
	multimap<wstring, TContactReg *>::iterator it;
	for (it = ContactRegList.begin(); it != ContactRegList.end(); it++)
		if (ElementIs(this, it->second->ClsID) && it->second->Dir == _Dir) {
			if (!Prolog)
				Code += wstring(L"$pow") + it->second->CntID + wstring(L",");
			if (DummyPrologVars)
				if (_Dir == dirInput)
					Code += Prepend + wstring(L"_,");
				else
					Code += Prepend + wstring(L"'null',");
			else
				Code += wstring(Prepend) + it->second->CntID + wstring(L",");
			Result = true;
		}
	return Result;
}

bool TElementReg::GeneratePHP(wstring & Code) {
	bool Result = true;
	if (!Generated) {
		Generated = true;
		if (Parent) 
			Result = Parent->GeneratePHP(Code);
		if (Result) {
			Code += wstring(L"class ") + ClsID;
			if (Parent)
				Code += wstring(L" extends ") + Parent->ClsID;
			Code += L" {\r\n";
			Code += wstring(L"  var $") + wstring(idfieldClassID) +
				wstring(L" = \"") + wstring(ClsID) + wstring(L"\";\r\n");
			if (!Parent)
				Code += wstring(L"  var $") + wstring(idfieldID) +
					wstring(L";\r\n");
			multimap<wstring, TParameter *>::iterator it;
			for (it = Params.begin(); it != Params.end(); it++)
				if (!it->second->Redefined)
					Code += wstring(L"  var $") + it->second->Name +
						wstring(L";\r\n");
			multimap<wstring, TParameter *> AllParams;
			CollectParams(AllParams);
			if (getUsed()) {
				Code += wstring(L"\r\n  function ") + ClsID +
					wstring(L"($_") + wstring(idfieldID) + wstring(L",");
				for (it = AllParams.begin(); it != AllParams.end(); it++)
					if (!it->second->Redefined)
						Code += wstring(L"$_") + it->second->Name + wstring(L",");
				Code[Code.length()-1] = ')';
				Code += wstring(L" {\r\n") +
					wstring(L"    $this->") + wstring(idfieldID) +
					wstring(L" = $_") + wstring(idfieldID) +
					wstring(L";\r\n");
				for (it = AllParams.begin(); it != AllParams.end(); it++)
					if (!it->second->Redefined)
						Code += wstring(L"    $this->") + it->second->Name +
						 wstring(L" = $_") + it->second->Name +
						 wstring(L";\r\n");
				Code += wstring(L"  }\r\n");
			}
			if (FUsed || !Parent) {
				Code += wstring(L"\r\n  function ") + wstring(idfunGenerate) +
					ClsID + wstring(L"($") + wstring(idprmStage) + wstring(L",");
				ProducePrms(false, Code, dirInput, wstring(L"$"));
				ProducePrms(false, Code, dirOutput, wstring(L"&$"));
				Code[Code.length()-1] = ')';
				Code += wstring(L"\r\n  {\r\n");
				if (Inherit) {
					TElementReg * P = Parent;
					while (P && P->Script.length() == 0)
						P = P->Parent;
					if (P) {
						Code += wstring(L"   ") + P->ClsID + wstring(L"::") +
							wstring(idfunGenerate) + P->ClsID + (L"($") +
							wstring(idprmStage) + wstring(L",");
						P->ProducePrms(false, Code, dirInput, wstring(L"$"));
						P->ProducePrms(false, Code, dirOutput, wstring(L"$"));
						Code[Code.length()-1] = ')';
						Code += L";\r\n";
					}
				}
				Code += L"   ob_start();\r\n";
				wstring _Script = Script;
				if (_Script.length() > wstring(tagPHPOpen).length( ) +wstring(tagPHPClose).length() + 2) {
					if (_Script.substr(0, wstring(tagPHPOpen).length()) == wstring(tagPHPOpen))
						_Script.erase(_Script.begin(), _Script.begin() + wstring(tagPHPOpen).length());
					if (_Script.substr(_Script.length() - wstring(tagPHPClose).length() - 2) == wstring(tagPHPClose) + wstring(L"\r\n"))
						_Script.erase(_Script.end() - wstring(tagPHPClose).length() - 2, _Script.end());
				}
				Code += ShiftRight(_Script, 3) + wstring(L"\r\n");
				Code += wstring(L"   $output = ob_get_contents();\r\n") +
				  wstring(L"   ob_end_flush();\r\n") +
				  wstring(L"   StoreMapped(\"") + ClsID +
				  wstring(L"\", $output);\r\n");
				Code += L"  }\r\n";
			}
			Code += L"}\r\n\r\n";
		}
	}
	return Result;
}

TContact::~TContact() {
	while (Links.size())
		delete Links[0];
}

TElement::TElement(TElementReg * _Ref, const wstring & ID, int Flgs) :
		Ref(_Ref), Ident(ID), Flags(Flgs) {
	multimap<wstring, TParameter *> Prms;
	Ref->CollectParams(Prms);
	multimap<wstring, TParameter *>::iterator itp;
	for (itp = Prms.begin(); itp != Prms.end(); itp++) {
		Parameters[itp->second->Name] = itp->second->DefValue;
		ParameterObjs[itp->second->Name] = itp->second;
	}
	multimap<wstring, TContactReg *>::iterator itc;
	for (itc = ContactRegList.begin(); itc != ContactRegList.end(); itc++) {
		if (ElementIs(Ref, itc->second->ClsID)) {
			if (!AddContact(itc->second->CntID, itc->second->Name, itc->second))
				throw logic_error("Can't add contact!");
		}
	}
	X = 0;
	Y = 0;
}

void TElement::Move(int x, int y) {
	X = x;
	Y = y;
}

TContact * TElement::AddContact(const wstring & ID, const wstring & Name,
	TContactReg * _Ref) {
	map<wstring, TContact *> & Contacts = _Ref->Dir == dirInput ? Inputs : Outputs;
	map<wstring, TContact *>::iterator itc = Contacts.find(ID);
	if (itc != Contacts.end())
		return NULL;
	TContact * result = new TContact(Name, this, _Ref);
	Contacts[ID] = result;
	return result;
}

TElement::~TElement() {
	map<wstring, TContact *>::iterator iti;
	for (iti = Inputs.begin(); iti != Inputs.end(); iti++)
		delete iti->second;
	map<wstring, TContact *>::iterator ito;
	for (ito = Outputs.begin(); ito != Outputs.end(); ito++)
		delete ito->second;
}

TElement * TSystem::GetElement(const wstring & ID) {
	map<wstring, TElement *>::iterator ite = Elements.find(ID);
	return ite == Elements.end() ? NULL : ite->second;
}

TElement * TSystem::AddElement(const wstring & CID, const wstring & ID, int Flgs) {
	map<wstring, TElementReg *>::iterator itr = ElementRegList.find(CID);
	if (itr == ElementRegList.end())
		return NULL;
	else {
		TElement * result = new TElement(itr->second, ID, Flgs);
		Elements[ID] = result;
		return result;
	}
}

int TElement::Check() {
	auto _Check = [&](const map<wstring, TContact *> & Contacts)->int {
		int Result = rsOk;
		map<wstring, TContact *>::const_iterator itc = Contacts.begin();
		while (itc != Contacts.end()) {
			TContact * C = itc->second;
			if (C->Ref->Required && C->Links.size() == 0)
				Result = rsNonStrict;
			if (C->Ref->MaxArity == 1 && C->Links.size() > 1)
				return rsStrict;
			itc++;
		}
		return Result;
	};

	int Result;
	Flags |= flChecked;
	Ref->setUsed(true);
	int C1 = _Check(Inputs);
	if (C1 == rsOk)
		Result = _Check(Outputs);
	else if (C1 == rsStrict)
		Result = rsStrict;
	else if (_Check(Outputs) == rsStrict)
		Result = rsStrict;
	else
		Result = rsNonStrict;
	map<wstring, TContact *>::iterator itc = Outputs.begin();
	while (itc != Outputs.end() && Result != rsStrict) {
		int j = 0;
		wstring OID = itc->first;
		while (j < itc->second->Links.size() && Result != rsStrict) {
			wstring IID = itc->second->Links[j]->_To->Ref->CntID;
			int St = Result;
			Result = rsStrict;
			multimap<wstring, TLinkReg *>::iterator itl = LinkRegList.begin();
			while (itl != LinkRegList.end()) {
				if (ElementIs(itc->second->Links[j]->_From->Owner->Ref, itl->second->OutClsID) &&
					ElementIs(itc->second->Links[j]->_To->Owner->Ref, itl->second->InClsID) &&
					(IID == itl->second->InContID) &&
					(OID == itl->second->OutContID)) {
					Result = St;
					break;
				}
				itl++;
			}
			j++;
		}
		itc++;
	}
	return Result;
}

void TElement::FindConnectedByType(const wstring & ClsID, TIODirection Dir,
	vector<TElement *> & objs
	) {

	auto Find = [&](const map<wstring, TContact *> & Contacts, TIODirection _Dir) {
		map<wstring, TContact *>::const_iterator itc;
		for (itc = Contacts.begin(); itc != Contacts.end(); itc++) {
			TContact * C = itc->second;
			for (TLink * L : C->Links) {
				if (!L->Inform)
				if (_Dir == dirInput && (ClsID.length() == 0 || ElementIs(L->_From->Owner->Ref, ClsID)))
					objs.push_back(L->_From->Owner);
				else if (_Dir == dirOutput && (ClsID.length() == 0 || ElementIs(L->_To->Owner->Ref, ClsID)))
					objs.push_back(L->_To->Owner);
			}
		}
	};

	objs.clear();
	if (Dir & dirInput) Find(Inputs, dirInput);
	if (Dir & dirOutput) Find(Outputs, dirOutput);
}

bool TSystem::GeneratePHP(wstring & Code) {
	ClearFlags(flAllTemporary);
	map<wstring, TElementReg *>::iterator it = ElementRegList.begin();
	while (it != ElementRegList.end()) {
		it->second->Generated = false;
		it->second->setUsed(false);
		it++;
	}
	Code = wstring(ScriptPrepend) + wstring(L"\r\n");
	bool Result = Check() == rsOk && MakeCascade(flClassesGenerated, Code) == rsOk;
	if (Result) {
		Code += GenerateText(
			L"for ($$[0] = $$[1][0]; $$[2] > 0; $$[0] = $[3]())\r\n{\r\n",
			4, idvarStage, idvarEvents, idvarNumEvents, idfunNextEvent
		);
		wstring CallsCode;
		Result = MakeCascade(flCallsGenerated, CallsCode) == rsOk;
		CallsCode +=
			GenerateText(
				L"if ($$[0] !== \"\")\r\n   eval($$[0]);\r\n",
				1, idvarTape
			);
		if (Result)
			Code +=
				ShiftRight(CallsCode, 1) +
				wstring(L"}\r\n");
	}
	Code += wstring(ScriptPost) + wstring(L"\r\n");
	return Result;
}

bool TElement::GenerateClasses(wstring & Code) {
	Flags |= flClassesGenerated;
	bool Result = Ref->GeneratePHP(Code);
	if (Result) {
		Code += wstring(L"$") + Ident + wstring(L" = new ") + Ref->ClsID +
			wstring(L"(\"") + Ident + wstring(L"\",");
		multimap<wstring, TParameter *> AllParams;
		Ref->CollectParams(AllParams);
		multimap<wstring, TParameter *>::iterator it;
		for (it = AllParams.begin(); it != AllParams.end(); it++)
			if (!it->second->Redefined) {
				wstring S = Parameters[it->second->Name];
				wchar_t * meta[3] = { L"\\", L"\"", L"$" };
				for (int j = 0; j < sizeof(meta) / sizeof(wchar_t *); j++)
					S = ReplaceAll(S, wstring(meta[j]), wstring(L"\\") + wstring(meta[j]));
				S = ReplaceAll(S, L"\t", L"\\t");
				S = ReplaceAll(S, L"\r\n", L"\\n");
				Code += wstring(L"\"") + S + wstring(L"\",");
		}
		Code[Code.length()-1] = ')';
		Code += wstring(L";\r\n\r\n");
	}
	return Result;
}

bool TElement::GenerateCalls(wstring & Code) {
	auto GetOutDefinition = [&](TContact * _Out)->wstring {
		wstring Result = wstring(L"array(\"_ClassID\" => array(\"") +
			_Out->Owner->Ref->ClsID + wstring(L"\"), ");
		Result += wstring(L"\"_ID\" => array(\"") +
			_Out->Owner->Ident + wstring(L"\"), ");
		Result += wstring(L"\"_LinkID\" => array(\"") +
			_Out->Ref->CntID + wstring(L"\"))");
		return Result;
	};

	char buf[128];
	Flags |= flCallsGenerated;
	map<wstring, TContact *>::iterator it;
	for (it = Outputs.begin(); it != Outputs.end(); it++)
		Code += wstring(L"$") + Ident + wstring(L"_") + it->first +
			wstring(L" = ") + GetOutDefinition(it->second) + wstring(L";\r\n");
	Code += wstring(L"$") + Ident + wstring(L"->") + wstring(idfunGenerate) +
		Ref->ClsID + wstring(L"($") + wstring(idvarStage) + wstring(L",");
	for (it = Inputs.begin(); it != Inputs.end(); it++) {
		sprintf(buf, "%i", it->second->Links.size());
		Code += utf8_to_wstring(buf) + wstring(L",");
		if (it->second->Links.size() == 0)
			Code += wstring(L"array(),");
		else {
			if (it->second->Links.size() > 1)
				Code += L"contact_merge(array(";
			for (TLink * L : it->second->Links)
				if (L->Inform)
					Code += GetOutDefinition(L->_From) + wstring(L",");
				else 
					Code += wstring(L"$") + L->_From->Owner->Ident + wstring(L"_") +
						L->_From->Ref->CntID + wstring(L",");
				if (it->second->Links.size() > 1) {
					Code[Code.length()-1] = ')';
					Code += L"),";
				}
		}
	}
	for (it = Outputs.begin(); it != Outputs.end(); it++) {
		sprintf(buf, "%i", it->second->Links.size());
		Code += utf8_to_wstring(buf) + wstring(L",$") + Ident +
			wstring(L"_") + it->first + wstring(L",");
	}
	Code[Code.length()-1] = ')';
	Code += wstring(L";\r\n\r\n");
	return true;
}

wstring TElement::ToString() {
	wstring Result = Ref->ClsID;
	Result += L":";
	Result += Ident;
	Result += L" is ";
	multiset<wstring> L;
	map<wstring, wstring>::iterator itp;
	for (itp = Parameters.begin(); itp != Parameters.end(); itp++) {
		wstring P = itp->first;
		P += L"=";
		P += itp->second;
		P += L",";
		L.insert(P);
	}
	for (const wstring & S : L)
		Result += S;
	Result += L") : [";
	L.clear();
	map<wstring, TContact *>::iterator itc;
	for (itc = Outputs.begin(); itc != Outputs.end(); itc++)
	for (TLink * LL : itc->second->Links) {
		wstring P = itc->second->Ref->CntID;
		P += L"->";
		P += LL->_To->Owner->Ident;
		P += L":";
		P += LL->_To->Ref->CntID;
		P += L",";
		L.insert(P);
	}
	for (const wstring & S : L)
		Result += S;
	Result += L"];";
	return Result;
}

TLink * TSystem::AddLink(TContact * _From, TContact * _To, bool Inf) {
	if (_From && _To) {
		for (TLink * L : _From->Links)
			if (L->_To == _To)
				return L;
		for (TLink * L : _To->Links)
			if (L->_From == _From)
				return L;
		TLink * result = new TLink(_From, _To, Inf);
		_From->Links.push_back(result);
		_To->Links.push_back(result);
		return result;
	}
	else
		return NULL;
}

bool TSystem::LoadFromXML(wstring & Lang, const wstring & inFileName) {
	XMLDocument dom;
	if (dom.LoadFile(wstring_to_utf8(inFileName).c_str()) != XML_SUCCESS)
		return false;
	bool Result = true;
	XMLElement * D = dom.RootElement();
	const char * _Lang = D->Attribute("Lang");
	if (_Lang)
		Lang = utf8_to_wstring(string(_Lang));
	else
		Lang = L"";
	XMLElement * Els = D->FirstChildElement("Elements");
	XMLElement * _El = Els->FirstChildElement("Element");
	int NumElems;
	sscanf(Els->Attribute("NumItems"), "%i", &NumElems);

	for (int i = 0; i < NumElems; i++) {
		wstring CID = utf8_to_wstring(_El->Attribute("ClassID"));
		wstring ID = utf8_to_wstring(_El->Attribute("ID"));
		TElement * E = AddElement(CID, ID, 0);
		if (E) {
			XMLElement * El = _El->FirstChildElement("Parameters");
			int N;
			sscanf(El->Attribute("NumItems"), "%i", &N);
			XMLElement * __El = El->FirstChildElement("Parameter");
			for (int j = 0; j < N; j++) {
				wstring Str = utf8_to_wstring(__El->Attribute("ID"));
				map<wstring, wstring>::iterator it = E->Parameters.find(Str);
				if (it != E->Parameters.end()) {
					it->second = utf8_to_wstring(__El->GetText());
				}
				__El = __El->NextSiblingElement("Parameter");
			}
			El = _El->FirstChildElement("Position");
			sscanf(El->Attribute("Left"), "%i", &E->X);
			sscanf(El->Attribute("Top"), "%i", &E->Y);
		}
		else
			return false;
		_El = _El->NextSiblingElement("Element");
	}
	_El = Els->FirstChildElement("Element");
	for (int i = 0; i < NumElems; i++) {
		XMLElement * _Item = _El->FirstChildElement("OutputLinks");
		TElement * E = Elements[utf8_to_wstring(_El->Attribute("ID"))];
		if (!_Item->NoChildren()) {
			XMLElement * Item = _Item->FirstChildElement("Contact");
			while (Item) {
				wstring ID = utf8_to_wstring(Item->Attribute("ID"));
				XMLElement * Lnk = Item->FirstChildElement("Link");
				while (Lnk) {
					TElement * E1 = GetElement(utf8_to_wstring(Lnk->Attribute("ElementID")));
					wstring ID1 = utf8_to_wstring(Lnk->Attribute("ContID"));
					AddLink(E->Outputs[ID], E1->Inputs[ID1],
						utf8_to_wstring(Lnk->Attribute("Informational")) == L"True");
					Lnk = Lnk->NextSiblingElement("Link");
				}
				Item = Item->NextSiblingElement("Contact");
			}
		}
		_El = _El->NextSiblingElement("Element");
	}
	return Result;
}

void TSystem::SaveToXML(const wstring & outFileName) {
	std::ofstream out(wstring_to_utf8(outFileName));
	if (out) {
		out << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << endl;
		out << "<!DOCTYPE System [" << endl;
		out << "<!ELEMENT System (Elements)>" << endl;
		out << "<!ATTLIST System" << endl;
		out << "Lang CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT Elements (Element*)>" << endl;
		out << "<!ATTLIST Elements" << endl;
		out << "NumItems CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT Element (Show,Position,Parameters,InternalInputs,InternalOutputs,PublishedInputs,PublishedOutputs,InputLinks,OutputLinks)>" << endl;
		out << "<!ATTLIST Element" << endl;
		out << "ClassID CDATA #REQUIRED" << endl;
		out << "ParentID CDATA #REQUIRED" << endl;
		out << "ID ID #REQUIRED" << endl;
		out << "Permanent (True | False) #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT Show EMPTY>" << endl;
		out << "<!ATTLIST Show" << endl;
		out << "Class (True | False) #REQUIRED" << endl;
		out << "Name (True | False) #REQUIRED" << endl;
		out << "Image (True | False) #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT Position EMPTY>" << endl;
		out << "<!ATTLIST Position" << endl;
		out << "Left CDATA #REQUIRED" << endl;
		out << "Top CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT Parameters (Parameter*)>" << endl;
		out << "<!ATTLIST Parameters" << endl;
		out << "NumItems CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT Parameter (#PCDATA | EMPTY)*>" << endl;
		out << "<!ATTLIST Parameter" << endl;
		out << "ID CDATA #REQUIRED" << endl;
		out << "Indent CDATA #IMPLIED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT InternalInputs (iContact*)>" << endl;
		out << "<!ATTLIST InternalInputs" << endl;
		out << "NumItems CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT InternalOutputs (iContact*)>" << endl;
		out << "<!ATTLIST InternalOutputs" << endl;
		out << "NumItems CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT iContact EMPTY>" << endl;
		out << "<!ATTLIST iContact" << endl;
		out << "ID CDATA #REQUIRED" << endl;
		out << "ElementID IDREF #REQUIRED" << endl;
		out << "ContID CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT PublishedInputs (pContact*)>" << endl;
		out << "<!ATTLIST PublishedInputs" << endl;
		out << "NumItems CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT PublishedOutputs (pContact*)>" << endl;
		out << "<!ATTLIST PublishedOutputs" << endl;
		out << "NumItems CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT pContact EMPTY>" << endl;
		out << "<!ATTLIST pContact" << endl;
		out << "ID CDATA #REQUIRED" << endl;
		out << "PublicID CDATA #REQUIRED" << endl;
		out << "PublicName CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT InputLinks (Contact*)>" << endl;
		out << "<!ELEMENT OutputLinks (Contact*)>" << endl;
		out << "<!ELEMENT Contact (Link*)>" << endl;
		out << "<!ATTLIST Contact" << endl;
		out << "ID CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT Link (Points?)>" << endl;
		out << "<!ATTLIST Link" << endl;
		out << "ElementID IDREF #REQUIRED" << endl;
		out << "ContID CDATA #REQUIRED" << endl;
		out << "Color CDATA #IMPLIED" << endl;
		out << "Informational (True | False) #REQUIRED" << endl;
		out << ">" << endl;
		out << "<!ELEMENT Points (#PCDATA | EMPTY)*>" << endl;
		out << "<!ATTLIST Points" << endl;
		out << "NumItems CDATA #REQUIRED" << endl;
		out << ">" << endl;
		out << "]>" << endl;
		out << "<System Lang=\"\">" << endl;
		out << "<Elements NumItems = \"" << Elements.size() << "\">" << endl;
		map<wstring, TElement *>::iterator it = Elements.begin();
		while (it != Elements.end()) {
			out << "<Element ClassID = " << it->second->Ref->ClsID <<
				" ParentID = \"\" ID = " << it->first << " Permanent = \"False\">" << endl;
			out << "<Show Class = \"True\" Name = \"True\" Image = \"False\" />" << endl;
			out << "<Position Left = \"" << it->second->X << "\" Top = \"" << it->second->Y << "\" />" << endl;
			if (it->second->Parameters.size()) {
				out << "<Parameters NumItems = \"" << it->second->Parameters.size() << "\">" << endl;
				map<wstring, wstring>::iterator itp = it->second->Parameters.begin();
				while (itp != it->second->Parameters.end()) {
					out << "<Parameter ID = " << itp->first <<
						" Indent = \"0\">";
					string buf = wstring_to_utf8(itp->second);
					out.write(buf.c_str(), buf.length());
					out << "</Parameter>" << endl;
					itp++;
				}
				out << "</Parameters>" << endl;
			}
			else
				out << "<Parameters NumItems = \"0\" />" << endl;
			out << "<InternalInputs NumItems = \"0\"/>" << endl;
			out << "<InternalOutputs NumItems = \"0\"/>" << endl;
			out << "<PublishedInputs NumItems = \"0\"/>" << endl;
			out << "<PublishedOutputs NumItems = \"0\"/>" << endl;
			if (it->second->Inputs.size()) {
				out << "<InputLinks>" << endl;
				map<wstring, TContact *>::iterator iti = it->second->Inputs.begin();
				while (iti != it->second->Inputs.end()) {
					if (iti->second->Links.size()) {
						out << "<Contact ID = " << iti->first << ">" << endl;
						for (TLink * L : iti->second->Links) {
							out << "<Link ElementID = " << L->_From->Owner->Ident <<
								" ContID = " << L->_From->Ref->CntID << " Informational = \"" <<
								(L->Inform ? "True" : "False") << "\" />" << endl;
						}
						out << "</Contact>" << endl;
					}
					iti++;
				}
				out << "</InputLinks>" << endl;
			}
			else
				out << "<InputLinks/>" << endl;
			if (it->second->Outputs.size()) {
				out << "<OutputLinks>" << endl;
				map<wstring, TContact *>::iterator ito = it->second->Outputs.begin();
				while (ito != it->second->Outputs.end()) {
					if (ito->second->Links.size()) {
						out << "<Contact ID = " << ito->first << ">" << endl;
						for (TLink * L : ito->second->Links) {
							out << "<Link ElementID = " << L->_To->Owner->Ident <<
								" ContID = " << L->_To->Ref->CntID << " Color = \"clBlack\" Informational = \"" <<
								(L->Inform ? "True" : "False") << "\">" << endl;
							out << "<Points NumItems = \"0\" />" << endl;
							out << "</Link>" << endl;
						}
						out << "</Contact>" << endl;
					}
					ito++;
				}
				out << "</OutputLinks>" << endl;
			}
			else
				out << "<OutputLinks/>" << endl;
			out << "</Element>" << endl;
			it++;
		}
		out << "</Elements>" << endl;
		out << "</System>" << endl;
		out.close();
	}
}

bool TSystem::Reach(TElement * Obj, int nTo, void ** _To) {
	int i = 0;
	bool Result = false;
	Obj->SetFlags(flChecked);
	while (i < nTo && !Result)
		if (_To[i] == Obj)
			Result = true;
		else
			i++;

	if (!Result) {
		vector<TElement *> Connexant;
		Obj->FindConnectedByType(L"", dirOutput, Connexant);
		int i = 0;
		while (i < Connexant.size() && !Result) {
			if ((Connexant[i]->Flags & flChecked) == 0)
				if (Reach(Connexant[i], nTo, _To))
					Result = true;
				else
					i++;
			else
				i++;
		}
	}

	return Result;
}

int TSystem::Check() {
	wstring P;
	return MakeCascade(flChecked, P);
}

int TSystem::Cascade(TElement * Obj, int Flag, wstring & Parameter) {
	int Result = rsOk;
	vector<TElement *> C;
	Obj->FindConnectedByType(L"", dirInput, C);
	bool Found = false;
	for (TElement * E : C) {
		if ((E->Flags & Flag) == 0) {
			Found = true;
			break;
		}
	}
	if (!Found) {
		if ((Obj->Flags & Flag) == 0) {
			switch (Flag) {
				case flChecked: Result = Obj->Check(); break;
				case flClassesGenerated: if (Obj->GenerateClasses(Parameter))
											Result = rsOk;
										 else
											Result = rsStrict;
										break;
				case flCallsGenerated: if (Obj->GenerateCalls(Parameter))
											Result = rsOk;
										else
											Result = rsStrict;
										break;
				case flPredicatesGenerated: Result = rsOk;
			}
			if (Result != rsStrict) {
				vector<TElement *> C1;
				Obj->FindConnectedByType(L"", dirOutput, C1);
				for (TElement * E1 : C1)
					switch (Cascade(E1, Flag, Parameter)) {
						case rsNonStrict: Result = rsNonStrict; break;
						case rsStrict: return rsStrict;
					}
			}
		}
	}
	return Result;
}

int TSystem::MakeCascade(int Flag, wstring & Parameter) {
	int Result = rsOk;
	map<wstring, TElement *>::iterator ite = Elements.begin();
	while (ite != Elements.end()) {
		if ((ite->second->Flags & Flag) == 0) {
			vector<TElement *> C;
			ite->second->FindConnectedByType(L"", dirInput, C);
			if (C.size() == 0)
				switch (Cascade(ite->second, Flag, Parameter)) {
					case rsNonStrict: Result = rsNonStrict; break;
					case rsStrict: return rsStrict;
				}
		}
		ite++;
	}
	return Result;
}

bool TSystem::Cycled(vector<TElement *> & ObjList, TElement * Obj, TElement * LinkedObj) {
	bool Result = Obj == LinkedObj;

	if (!(Result || find(ObjList.begin(), ObjList.end(), Obj) != ObjList.end())) {
		ObjList.push_back(Obj);
		vector<TElement *> C;
		Obj->FindConnectedByType(L"", dirOutput, C);
		for (TElement * E : C)
			if (Cycled(ObjList, E, LinkedObj))
				return true;
	}

	return Result;
}

void TSystem::AnalyzeLinkStatus(TLink * L) {
	if (L && !L->Inform) {
		vector<TElement *> C;
		L->Inform = Cycled(C, L->_To->Owner, L->_From->Owner);
	}
}

wstring TSystem::ToString() {
	multiset<wstring> L;
	map<wstring, TElement *>::iterator it;
	for (it = Elements.begin(); it != Elements.end(); it++)
		L.insert(it->second->ToString());
	wstring Result;
	for (const wstring & S : L) {
		Result += S;
		Result += L";";
	}

	return Result;
}

void * CreateSysF() {
	return new TSystem();
}

bool ExistClassF(const char * ClsID) {
	return FindElementRegByID(utf8_to_wstring(ClsID)) != NULL;
}

void * GetElementF(void * Sys, char * ID) {
	TSystem * sys = (TSystem *) Sys;
	return sys->GetElement(utf8_to_wstring(ID));
}

bool CanReachF(void * Sys, void *_From, int nTo, void **_To) {
	TSystem * sys = (TSystem *)Sys;
	sys->ClearFlags(flChecked);
	bool result = sys->Reach((TElement *)_From, nTo, _To);
	sys->ClearFlags(flChecked);
	return result;
}

void CreateContactsF(char * ClassID, int _Dir, void * dom, void * Parent, char * Tag) {
	TElementReg * Ref = FindElementRegByID(utf8_to_wstring(ClassID));

	if (!Ref) return;

	multimap<wstring, TContactReg *>::iterator it;
	for (it = ContactRegList.begin(); it != ContactRegList.end(); it++)
		if (ElementIs(Ref, it->second->ClsID) && _Dir == it->second->Dir)
			CreateDOMContact(dom, Parent, Tag, wstring_to_utf8(it->second->CntID).c_str());
}

void * AddElementF(void * Sys, char * ClassName, char * ID, int Flags) {
	return ((TSystem *)Sys)->AddElement(utf8_to_wstring(ClassName), utf8_to_wstring(ID), Flags);
}

void * AddLinkF(void * Sys, void * El, char * ContID, void * PEl, char * PContID, char ** S, bool Info) {
	static char * retS = "";
	TContact * _From = ((TElement *)El)->Outputs[utf8_to_wstring(ContID)];
	TContact * _To = ((TElement *)PEl)->Inputs[utf8_to_wstring(PContID)];
	*S = retS;
	return ((TSystem *)Sys)->AddLink(_From, _To, Info);
}

bool AnalyzeLinkStatusIsInformF(void * sys, void * L) {
	((TSystem *)sys)->AnalyzeLinkStatus((TLink *)L);
	return ((TLink *)L)->Inform;
}

void SetParameterIfExistsF(void * el, char * PrmName, char * PrmValue) {
	TElement * Obj = (TElement *)el;
	map<wstring, wstring>::iterator it = Obj->Parameters.find(utf8_to_wstring(PrmName));
	if (it != Obj->Parameters.end())
		it->second = utf8_to_wstring(PrmValue);
}

void MoveF(void * el, int X, int Y) {
	((TElement *)el)->Move(X, Y);
}

int CheckSysF(void * Sys) {
	return ((TSystem *)Sys)->Check();
}

void ToStringF(void * Sys, char * Ret) {
	strcpy(Ret, wstring_to_utf8(((TSystem *)Sys)->ToString()).c_str());
}

void GenerateCodeF(void * Sys, char * Ret) {
	wstring Code;
	if (((TSystem *)Sys)->GeneratePHP(Code))
		strcpy(Ret, wstring_to_utf8(Code).c_str());
	else
		strcpy(Ret, "");
}

void SaveToXMLF(void * Sys, char * FName) {
	((TSystem *)Sys)->SaveToXML(utf8_to_wstring(string(FName)));
}

void _FreeF(void * Obj) {
	delete (TObject *)Obj;
}

bool NodeNameTester(char * NodeName, char * NodeTestString) {
	if (string(NodeTestString).substr(0, 3) == "cls" && FindElementRegByID(utf8_to_wstring(NodeTestString))) {
		TElementReg * Ref = FindElementRegByID(utf8_to_wstring(NodeName));
		return Ref && ElementIs(Ref, utf8_to_wstring(NodeTestString));
	}
	return false;
}
