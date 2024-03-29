
#define _CRT_SECURE_NO_WARNINGS
#include <map>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>


// Generated from ReentPreParser.g4 by ANTLR 4.9.2


#include "ReentPreParserListener.h"

#include "ReentPreParser.h"


using namespace antlrcpp;
using namespace antlr4;

ReentPreParser::ReentPreParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ReentPreParser::~ReentPreParser() {
  delete _interpreter;
}

std::string ReentPreParser::getGrammarFileName() const {
  return "ReentPreParser.g4";
}

const std::vector<std::string>& ReentPreParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ReentPreParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- TranslationUnitContext ------------------------------------------------------------------

ReentPreParser::TranslationUnitContext::TranslationUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::TranslationUnitContext::EOF() {
  return getToken(ReentPreParser::EOF, 0);
}

ReentPreParser::StatementseqContext* ReentPreParser::TranslationUnitContext::statementseq() {
  return getRuleContext<ReentPreParser::StatementseqContext>(0);
}


size_t ReentPreParser::TranslationUnitContext::getRuleIndex() const {
  return ReentPreParser::RuleTranslationUnit;
}

void ReentPreParser::TranslationUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTranslationUnit(this);
}

void ReentPreParser::TranslationUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTranslationUnit(this);
}

ReentPreParser::TranslationUnitContext* ReentPreParser::translationUnit() {
  TranslationUnitContext *_localctx = _tracker.createInstance<TranslationUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, ReentPreParser::RuleTranslationUnit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(207);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(206);
      statementseq();
      break;
    }

    default:
      break;
    }
    setState(209);
    match(ReentPreParser::EOF);

    		for (const std::string & s : scanner_refs)
    			if (scanners.find(s) == scanners.end())
    				std::cerr << "warning:" << std::string("unknown scanner '") << s <<
    						std::string("' in #add_scan/#add_parse/#scan/#parse directives") << std::endl;
    		std::map<std::string,int>::iterator it;
    		for (it = module_refs.begin(); it != module_refs.end(); it++)
    			if (modules.find(it->first) == modules.end())
    				throw FailedPredicateException(this, std::string("Unknown module '")+it->first+
    						std::string("' in some #def_pattern directives"));
    			else if (modules[it->first] != it->second)
    				throw FailedPredicateException(this, std::string("Module '")+it->first+
    						std::string("' was called with an incorrect parameters number in some #def_pattern directives"));
    	
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementseqContext ------------------------------------------------------------------

ReentPreParser::StatementseqContext::StatementseqContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::StatementContext *> ReentPreParser::StatementseqContext::statement() {
  return getRuleContexts<ReentPreParser::StatementContext>();
}

ReentPreParser::StatementContext* ReentPreParser::StatementseqContext::statement(size_t i) {
  return getRuleContext<ReentPreParser::StatementContext>(i);
}


size_t ReentPreParser::StatementseqContext::getRuleIndex() const {
  return ReentPreParser::RuleStatementseq;
}

void ReentPreParser::StatementseqContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementseq(this);
}

void ReentPreParser::StatementseqContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementseq(this);
}

ReentPreParser::StatementseqContext* ReentPreParser::statementseq() {
  StatementseqContext *_localctx = _tracker.createInstance<StatementseqContext>(_ctx, getState());
  enterRule(_localctx, 2, ReentPreParser::RuleStatementseq);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(213); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(212);
              statement();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(215); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

ReentPreParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::DefModuleContext* ReentPreParser::StatementContext::defModule() {
  return getRuleContext<ReentPreParser::DefModuleContext>(0);
}

tree::TerminalNode* ReentPreParser::StatementContext::DefModule() {
  return getToken(ReentPreParser::DefModule, 0);
}

ReentPreParser::DefMemoizationContext* ReentPreParser::StatementContext::defMemoization() {
  return getRuleContext<ReentPreParser::DefMemoizationContext>(0);
}

tree::TerminalNode* ReentPreParser::StatementContext::DefMemoization() {
  return getToken(ReentPreParser::DefMemoization, 0);
}

ReentPreParser::PreprocPassesContext* ReentPreParser::StatementContext::preprocPasses() {
  return getRuleContext<ReentPreParser::PreprocPassesContext>(0);
}

tree::TerminalNode* ReentPreParser::StatementContext::PreprocPasses() {
  return getToken(ReentPreParser::PreprocPasses, 0);
}

ReentPreParser::AddScanContext* ReentPreParser::StatementContext::addScan() {
  return getRuleContext<ReentPreParser::AddScanContext>(0);
}

tree::TerminalNode* ReentPreParser::StatementContext::AddScan() {
  return getToken(ReentPreParser::AddScan, 0);
}

ReentPreParser::ScanContext* ReentPreParser::StatementContext::scan() {
  return getRuleContext<ReentPreParser::ScanContext>(0);
}

tree::TerminalNode* ReentPreParser::StatementContext::Scan() {
  return getToken(ReentPreParser::Scan, 0);
}

ReentPreParser::AddParseContext* ReentPreParser::StatementContext::addParse() {
  return getRuleContext<ReentPreParser::AddParseContext>(0);
}

tree::TerminalNode* ReentPreParser::StatementContext::AddParse() {
  return getToken(ReentPreParser::AddParse, 0);
}

ReentPreParser::ParseContext* ReentPreParser::StatementContext::parse() {
  return getRuleContext<ReentPreParser::ParseContext>(0);
}

tree::TerminalNode* ReentPreParser::StatementContext::Parse() {
  return getToken(ReentPreParser::Parse, 0);
}

ReentPreParser::Def_patternContext* ReentPreParser::StatementContext::def_pattern() {
  return getRuleContext<ReentPreParser::Def_patternContext>(0);
}

tree::TerminalNode* ReentPreParser::StatementContext::DefPattern() {
  return getToken(ReentPreParser::DefPattern, 0);
}

ReentPreParser::Def_xpathContext* ReentPreParser::StatementContext::def_xpath() {
  return getRuleContext<ReentPreParser::Def_xpathContext>(0);
}

tree::TerminalNode* ReentPreParser::StatementContext::DefXPath() {
  return getToken(ReentPreParser::DefXPath, 0);
}

ReentPreParser::ObjCilkSpawnContext* ReentPreParser::StatementContext::objCilkSpawn() {
  return getRuleContext<ReentPreParser::ObjCilkSpawnContext>(0);
}

tree::TerminalNode* ReentPreParser::StatementContext::Cilk_spawn() {
  return getToken(ReentPreParser::Cilk_spawn, 0);
}

ReentPreParser::ObjCilkAssignContext* ReentPreParser::StatementContext::objCilkAssign() {
  return getRuleContext<ReentPreParser::ObjCilkAssignContext>(0);
}

std::vector<ReentPreParser::ObjCilkDesignatorContext *> ReentPreParser::StatementContext::objCilkDesignator() {
  return getRuleContexts<ReentPreParser::ObjCilkDesignatorContext>();
}

ReentPreParser::ObjCilkDesignatorContext* ReentPreParser::StatementContext::objCilkDesignator(size_t i) {
  return getRuleContext<ReentPreParser::ObjCilkDesignatorContext>(i);
}

ReentPreParser::ObjCilkSyncContext* ReentPreParser::StatementContext::objCilkSync() {
  return getRuleContext<ReentPreParser::ObjCilkSyncContext>(0);
}

tree::TerminalNode* ReentPreParser::StatementContext::Cilk_sync() {
  return getToken(ReentPreParser::Cilk_sync, 0);
}

ReentPreParser::OtherLineContext* ReentPreParser::StatementContext::otherLine() {
  return getRuleContext<ReentPreParser::OtherLineContext>(0);
}


size_t ReentPreParser::StatementContext::getRuleIndex() const {
  return ReentPreParser::RuleStatement;
}

void ReentPreParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void ReentPreParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}

ReentPreParser::StatementContext* ReentPreParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 4, ReentPreParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(266);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(217);
      defModule();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(218);
      match(ReentPreParser::DefModule);

      		throw FailedPredicateException(this, "Something wrong with module definition");
      	
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(220);
      defMemoization();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(221);
      match(ReentPreParser::DefMemoization);

      		throw FailedPredicateException(this, "Something wrong with memoization");
      	
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(223);
      preprocPasses();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(224);
      match(ReentPreParser::PreprocPasses);

      		throw FailedPredicateException(this, "Something wrong with '#preproc_passes(n)'");
      	
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(226);
      addScan();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(227);
      match(ReentPreParser::AddScan);

      		throw FailedPredicateException(this, "Something wrong with '#add_scan'");
      	
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(229);
      scan();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(230);
      match(ReentPreParser::Scan);

      		throw FailedPredicateException(this, "Something wrong with '#scan'");
      	
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(232);
      addParse();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(233);
      match(ReentPreParser::AddParse);

      		throw FailedPredicateException(this, "Something wrong with '#add_parse'");
      	
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(235);
      parse();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(236);
      match(ReentPreParser::Parse);

      		throw FailedPredicateException(this, "Something wrong with '#parse'");
      	
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(238);
      def_pattern();
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(239);
      match(ReentPreParser::DefPattern);

      		throw FailedPredicateException(this, "Something wrong with '#def_pattern'");
      	
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(241);
      def_xpath();
      break;
    }

    case 18: {
      enterOuterAlt(_localctx, 18);
      setState(242);
      match(ReentPreParser::DefXPath);

      		throw FailedPredicateException(this, "Something wrong with '#def_xpath'");
      	
      break;
    }

    case 19: {
      enterOuterAlt(_localctx, 19);
      setState(244);
      objCilkSpawn();
      break;
    }

    case 20: {
      enterOuterAlt(_localctx, 20);
      setState(246);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(245);
        objCilkAssign();
        break;
      }

      default:
        break;
      }
      setState(251);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
      while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1 + 1) {
          setState(248);
          objCilkDesignator(); 
        }
        setState(253);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
      }
      setState(254);
      match(ReentPreParser::Cilk_spawn);
       throw FailedPredicateException(this, "Obj-cilk_spawn expression is incorrect!"); 
      break;
    }

    case 21: {
      enterOuterAlt(_localctx, 21);
      setState(256);
      objCilkSync();
      break;
    }

    case 22: {
      enterOuterAlt(_localctx, 22);
      setState(260);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
      while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1 + 1) {
          setState(257);
          objCilkDesignator(); 
        }
        setState(262);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
      }
      setState(263);
      match(ReentPreParser::Cilk_sync);
       throw FailedPredicateException(this, "Obj-cilk_sync expression is incorrect!"); 
      break;
    }

    case 23: {
      enterOuterAlt(_localctx, 23);
      setState(265);
      otherLine();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_patternContext ------------------------------------------------------------------

ReentPreParser::Def_patternContext::Def_patternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Def_patternContext::DefPattern() {
  return getToken(ReentPreParser::DefPattern, 0);
}

tree::TerminalNode* ReentPreParser::Def_patternContext::AssignGreater() {
  return getToken(ReentPreParser::AssignGreater, 0);
}

tree::TerminalNode* ReentPreParser::Def_patternContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::Def_patternContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

ReentPreParser::RegexpsContext* ReentPreParser::Def_patternContext::regexps() {
  return getRuleContext<ReentPreParser::RegexpsContext>(0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_patternContext::Identifier() {
  return getTokens(ReentPreParser::Identifier);
}

tree::TerminalNode* ReentPreParser::Def_patternContext::Identifier(size_t i) {
  return getToken(ReentPreParser::Identifier, i);
}

ReentPreParser::Put_factContext* ReentPreParser::Def_patternContext::put_fact() {
  return getRuleContext<ReentPreParser::Put_factContext>(0);
}

std::vector<ReentPreParser::Def_pattern_paramContext *> ReentPreParser::Def_patternContext::def_pattern_param() {
  return getRuleContexts<ReentPreParser::Def_pattern_paramContext>();
}

ReentPreParser::Def_pattern_paramContext* ReentPreParser::Def_patternContext::def_pattern_param(size_t i) {
  return getRuleContext<ReentPreParser::Def_pattern_paramContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_patternContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Def_patternContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::Def_patternContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_pattern;
}

void ReentPreParser::Def_patternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_pattern(this);
}

void ReentPreParser::Def_patternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_pattern(this);
}

ReentPreParser::Def_patternContext* ReentPreParser::def_pattern() {
  Def_patternContext *_localctx = _tracker.createInstance<Def_patternContext>(_ctx, getState());
  enterRule(_localctx, 6, ReentPreParser::RuleDef_pattern);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(268);
    match(ReentPreParser::DefPattern);

    		regexp_vars.clear(); regexp_vars.insert("root");
    		regexp_refs.clear();
    		std::string call_macro;
    	
    setState(270);
    dynamic_cast<Def_patternContext *>(_localctx)->id = match(ReentPreParser::Identifier);

    		if (scanners.find((dynamic_cast<Def_patternContext *>(_localctx)->id != nullptr ? dynamic_cast<Def_patternContext *>(_localctx)->id->getText() : "")) != scanners.end())
    			throw FailedPredicateException(this, "Pattern is already defined");
    		scanners.insert((dynamic_cast<Def_patternContext *>(_localctx)->id != nullptr ? dynamic_cast<Def_patternContext *>(_localctx)->id->getText() : ""));
    	
    setState(272);
    match(ReentPreParser::AssignGreater);
    setState(276);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::LeftBracket: {
        setState(273);
        put_fact();
        break;
      }

      case ReentPreParser::Identifier: {
        setState(274);
        dynamic_cast<Def_patternContext *>(_localctx)->module = match(ReentPreParser::Identifier);

        				call_macro = (dynamic_cast<Def_patternContext *>(_localctx)->module != nullptr ? dynamic_cast<Def_patternContext *>(_localctx)->module->getText() : "");
        			
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(278);
    match(ReentPreParser::LeftParen);
     int param_count = 0; 
    setState(291);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(280);
      def_pattern_param();
       param_count++; 
      setState(288);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Comma) {
        setState(282);
        match(ReentPreParser::Comma);
        setState(283);
        def_pattern_param();
         param_count++; 
        setState(290);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    default:
      break;
    }
    setState(293);
    match(ReentPreParser::RightParen);

    		if (call_macro.length() > 0) {
    			if (module_refs.find(call_macro) != module_refs.end() && module_refs[call_macro] != param_count)
    				throw FailedPredicateException(this,
    					std::string("Pattern calls module '") + call_macro +
    					std::string("' with an incorrect number of params than in another patterns"));
    			else module_refs[call_macro] = param_count;
    		}
    	
    setState(295);
    regexps();

    		for (const std::string & s : regexp_refs)
    			if (regexp_vars.find(s) == regexp_vars.end())
    				throw FailedPredicateException(this,
    					std::string("Reference to undefined var '")+
    					s +
    					std::string("' in '#def_pattern' regexps/header"));
    	
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Put_factContext ------------------------------------------------------------------

ReentPreParser::Put_factContext::Put_factContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Put_factContext::LeftBracket() {
  return getToken(ReentPreParser::LeftBracket, 0);
}

tree::TerminalNode* ReentPreParser::Put_factContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::Put_factContext::RightBracket() {
  return getToken(ReentPreParser::RightBracket, 0);
}


size_t ReentPreParser::Put_factContext::getRuleIndex() const {
  return ReentPreParser::RulePut_fact;
}

void ReentPreParser::Put_factContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPut_fact(this);
}

void ReentPreParser::Put_factContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPut_fact(this);
}

ReentPreParser::Put_factContext* ReentPreParser::put_fact() {
  Put_factContext *_localctx = _tracker.createInstance<Put_factContext>(_ctx, getState());
  enterRule(_localctx, 8, ReentPreParser::RulePut_fact);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(298);
    match(ReentPreParser::LeftBracket);
    setState(299);
    match(ReentPreParser::Identifier);
    setState(300);
    match(ReentPreParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_pattern_paramContext ------------------------------------------------------------------

ReentPreParser::Def_pattern_paramContext::Def_pattern_paramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Def_pattern_paramContext::CharacterLiteral() {
  return getToken(ReentPreParser::CharacterLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Def_pattern_paramContext::EmptyAtom() {
  return getToken(ReentPreParser::EmptyAtom, 0);
}

tree::TerminalNode* ReentPreParser::Def_pattern_paramContext::LeftBracket() {
  return getToken(ReentPreParser::LeftBracket, 0);
}

tree::TerminalNode* ReentPreParser::Def_pattern_paramContext::RightBracket() {
  return getToken(ReentPreParser::RightBracket, 0);
}

std::vector<ReentPreParser::Def_pattern_paramContext *> ReentPreParser::Def_pattern_paramContext::def_pattern_param() {
  return getRuleContexts<ReentPreParser::Def_pattern_paramContext>();
}

ReentPreParser::Def_pattern_paramContext* ReentPreParser::Def_pattern_paramContext::def_pattern_param(size_t i) {
  return getRuleContext<ReentPreParser::Def_pattern_paramContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_pattern_paramContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Def_pattern_paramContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}

tree::TerminalNode* ReentPreParser::Def_pattern_paramContext::Or() {
  return getToken(ReentPreParser::Or, 0);
}

ReentPreParser::Simple_xpath_expressionContext* ReentPreParser::Def_pattern_paramContext::simple_xpath_expression() {
  return getRuleContext<ReentPreParser::Simple_xpath_expressionContext>(0);
}


size_t ReentPreParser::Def_pattern_paramContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_pattern_param;
}

void ReentPreParser::Def_pattern_paramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_pattern_param(this);
}

void ReentPreParser::Def_pattern_paramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_pattern_param(this);
}

ReentPreParser::Def_pattern_paramContext* ReentPreParser::def_pattern_param() {
  Def_pattern_paramContext *_localctx = _tracker.createInstance<Def_pattern_paramContext>(_ctx, getState());
  enterRule(_localctx, 10, ReentPreParser::RuleDef_pattern_param);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(323);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(302);
      match(ReentPreParser::CharacterLiteral);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(303);
      match(ReentPreParser::EmptyAtom);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(304);
      match(ReentPreParser::LeftBracket);
      setState(317);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
      case 1: {
        setState(305);
        def_pattern_param();
        setState(310);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ReentPreParser::Comma) {
          setState(306);
          match(ReentPreParser::Comma);
          setState(307);
          def_pattern_param();
          setState(312);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(315);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Or) {
          setState(313);
          match(ReentPreParser::Or);
          setState(314);
          def_pattern_param();
        }
        break;
      }

      default:
        break;
      }
      setState(319);
      match(ReentPreParser::RightBracket);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(320);
      simple_xpath_expression();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);

      		throw FailedPredicateException(this, "Unrecognized (prolog_fact/module)'s parameter");
      	
      setState(322);
      matchWildcard();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Simple_xpath_expressionContext ------------------------------------------------------------------

ReentPreParser::Simple_xpath_expressionContext::Simple_xpath_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Xpath_and_expressionContext *> ReentPreParser::Simple_xpath_expressionContext::xpath_and_expression() {
  return getRuleContexts<ReentPreParser::Xpath_and_expressionContext>();
}

ReentPreParser::Xpath_and_expressionContext* ReentPreParser::Simple_xpath_expressionContext::xpath_and_expression(size_t i) {
  return getRuleContext<ReentPreParser::Xpath_and_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Simple_xpath_expressionContext::Or_() {
  return getTokens(ReentPreParser::Or_);
}

tree::TerminalNode* ReentPreParser::Simple_xpath_expressionContext::Or_(size_t i) {
  return getToken(ReentPreParser::Or_, i);
}


size_t ReentPreParser::Simple_xpath_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleSimple_xpath_expression;
}

void ReentPreParser::Simple_xpath_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimple_xpath_expression(this);
}

void ReentPreParser::Simple_xpath_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimple_xpath_expression(this);
}

ReentPreParser::Simple_xpath_expressionContext* ReentPreParser::simple_xpath_expression() {
  Simple_xpath_expressionContext *_localctx = _tracker.createInstance<Simple_xpath_expressionContext>(_ctx, getState());
  enterRule(_localctx, 12, ReentPreParser::RuleSimple_xpath_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(325);
    xpath_and_expression();
    setState(330);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Or_) {
      setState(326);
      match(ReentPreParser::Or_);
      setState(327);
      xpath_and_expression();
      setState(332);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Xpath_and_expressionContext ------------------------------------------------------------------

ReentPreParser::Xpath_and_expressionContext::Xpath_and_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Xpath_rel_expressionContext *> ReentPreParser::Xpath_and_expressionContext::xpath_rel_expression() {
  return getRuleContexts<ReentPreParser::Xpath_rel_expressionContext>();
}

ReentPreParser::Xpath_rel_expressionContext* ReentPreParser::Xpath_and_expressionContext::xpath_rel_expression(size_t i) {
  return getRuleContext<ReentPreParser::Xpath_rel_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_and_expressionContext::And_() {
  return getTokens(ReentPreParser::And_);
}

tree::TerminalNode* ReentPreParser::Xpath_and_expressionContext::And_(size_t i) {
  return getToken(ReentPreParser::And_, i);
}


size_t ReentPreParser::Xpath_and_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleXpath_and_expression;
}

void ReentPreParser::Xpath_and_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterXpath_and_expression(this);
}

void ReentPreParser::Xpath_and_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitXpath_and_expression(this);
}

ReentPreParser::Xpath_and_expressionContext* ReentPreParser::xpath_and_expression() {
  Xpath_and_expressionContext *_localctx = _tracker.createInstance<Xpath_and_expressionContext>(_ctx, getState());
  enterRule(_localctx, 14, ReentPreParser::RuleXpath_and_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(333);
    xpath_rel_expression();
    setState(338);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::And_) {
      setState(334);
      match(ReentPreParser::And_);
      setState(335);
      xpath_rel_expression();
      setState(340);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Xpath_rel_expressionContext ------------------------------------------------------------------

ReentPreParser::Xpath_rel_expressionContext::Xpath_rel_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Xpath_mul_expressionContext *> ReentPreParser::Xpath_rel_expressionContext::xpath_mul_expression() {
  return getRuleContexts<ReentPreParser::Xpath_mul_expressionContext>();
}

ReentPreParser::Xpath_mul_expressionContext* ReentPreParser::Xpath_rel_expressionContext::xpath_mul_expression(size_t i) {
  return getRuleContext<ReentPreParser::Xpath_mul_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_rel_expressionContext::Less() {
  return getTokens(ReentPreParser::Less);
}

tree::TerminalNode* ReentPreParser::Xpath_rel_expressionContext::Less(size_t i) {
  return getToken(ReentPreParser::Less, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_rel_expressionContext::Greater() {
  return getTokens(ReentPreParser::Greater);
}

tree::TerminalNode* ReentPreParser::Xpath_rel_expressionContext::Greater(size_t i) {
  return getToken(ReentPreParser::Greater, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_rel_expressionContext::Assign() {
  return getTokens(ReentPreParser::Assign);
}

tree::TerminalNode* ReentPreParser::Xpath_rel_expressionContext::Assign(size_t i) {
  return getToken(ReentPreParser::Assign, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_rel_expressionContext::NotEqual() {
  return getTokens(ReentPreParser::NotEqual);
}

tree::TerminalNode* ReentPreParser::Xpath_rel_expressionContext::NotEqual(size_t i) {
  return getToken(ReentPreParser::NotEqual, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_rel_expressionContext::LessEqual() {
  return getTokens(ReentPreParser::LessEqual);
}

tree::TerminalNode* ReentPreParser::Xpath_rel_expressionContext::LessEqual(size_t i) {
  return getToken(ReentPreParser::LessEqual, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_rel_expressionContext::GreaterEqual() {
  return getTokens(ReentPreParser::GreaterEqual);
}

tree::TerminalNode* ReentPreParser::Xpath_rel_expressionContext::GreaterEqual(size_t i) {
  return getToken(ReentPreParser::GreaterEqual, i);
}


size_t ReentPreParser::Xpath_rel_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleXpath_rel_expression;
}

void ReentPreParser::Xpath_rel_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterXpath_rel_expression(this);
}

void ReentPreParser::Xpath_rel_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitXpath_rel_expression(this);
}

ReentPreParser::Xpath_rel_expressionContext* ReentPreParser::xpath_rel_expression() {
  Xpath_rel_expressionContext *_localctx = _tracker.createInstance<Xpath_rel_expressionContext>(_ctx, getState());
  enterRule(_localctx, 16, ReentPreParser::RuleXpath_rel_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(341);
    xpath_mul_expression();
    setState(346);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 83) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 83)) & ((1ULL << (ReentPreParser::Assign - 83))
      | (1ULL << (ReentPreParser::Less - 83))
      | (1ULL << (ReentPreParser::Greater - 83))
      | (1ULL << (ReentPreParser::NotEqual - 83))
      | (1ULL << (ReentPreParser::LessEqual - 83))
      | (1ULL << (ReentPreParser::GreaterEqual - 83)))) != 0)) {
      setState(342);
      _la = _input->LA(1);
      if (!(((((_la - 83) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 83)) & ((1ULL << (ReentPreParser::Assign - 83))
        | (1ULL << (ReentPreParser::Less - 83))
        | (1ULL << (ReentPreParser::Greater - 83))
        | (1ULL << (ReentPreParser::NotEqual - 83))
        | (1ULL << (ReentPreParser::LessEqual - 83))
        | (1ULL << (ReentPreParser::GreaterEqual - 83)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(343);
      xpath_mul_expression();
      setState(348);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Xpath_mul_expressionContext ------------------------------------------------------------------

ReentPreParser::Xpath_mul_expressionContext::Xpath_mul_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Xpath_plus_expressionContext *> ReentPreParser::Xpath_mul_expressionContext::xpath_plus_expression() {
  return getRuleContexts<ReentPreParser::Xpath_plus_expressionContext>();
}

ReentPreParser::Xpath_plus_expressionContext* ReentPreParser::Xpath_mul_expressionContext::xpath_plus_expression(size_t i) {
  return getRuleContext<ReentPreParser::Xpath_plus_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_mul_expressionContext::Star() {
  return getTokens(ReentPreParser::Star);
}

tree::TerminalNode* ReentPreParser::Xpath_mul_expressionContext::Star(size_t i) {
  return getToken(ReentPreParser::Star, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_mul_expressionContext::Div() {
  return getTokens(ReentPreParser::Div);
}

tree::TerminalNode* ReentPreParser::Xpath_mul_expressionContext::Div(size_t i) {
  return getToken(ReentPreParser::Div, i);
}


size_t ReentPreParser::Xpath_mul_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleXpath_mul_expression;
}

void ReentPreParser::Xpath_mul_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterXpath_mul_expression(this);
}

void ReentPreParser::Xpath_mul_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitXpath_mul_expression(this);
}

ReentPreParser::Xpath_mul_expressionContext* ReentPreParser::xpath_mul_expression() {
  Xpath_mul_expressionContext *_localctx = _tracker.createInstance<Xpath_mul_expressionContext>(_ctx, getState());
  enterRule(_localctx, 18, ReentPreParser::RuleXpath_mul_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(349);
    xpath_plus_expression();
    setState(354);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Star

    || _la == ReentPreParser::Div) {
      setState(350);
      _la = _input->LA(1);
      if (!(_la == ReentPreParser::Star

      || _la == ReentPreParser::Div)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(351);
      xpath_plus_expression();
      setState(356);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Xpath_plus_expressionContext ------------------------------------------------------------------

ReentPreParser::Xpath_plus_expressionContext::Xpath_plus_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Xpath_unary_expressionContext *> ReentPreParser::Xpath_plus_expressionContext::xpath_unary_expression() {
  return getRuleContexts<ReentPreParser::Xpath_unary_expressionContext>();
}

ReentPreParser::Xpath_unary_expressionContext* ReentPreParser::Xpath_plus_expressionContext::xpath_unary_expression(size_t i) {
  return getRuleContext<ReentPreParser::Xpath_unary_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_plus_expressionContext::Plus() {
  return getTokens(ReentPreParser::Plus);
}

tree::TerminalNode* ReentPreParser::Xpath_plus_expressionContext::Plus(size_t i) {
  return getToken(ReentPreParser::Plus, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_plus_expressionContext::Minus() {
  return getTokens(ReentPreParser::Minus);
}

tree::TerminalNode* ReentPreParser::Xpath_plus_expressionContext::Minus(size_t i) {
  return getToken(ReentPreParser::Minus, i);
}


size_t ReentPreParser::Xpath_plus_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleXpath_plus_expression;
}

void ReentPreParser::Xpath_plus_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterXpath_plus_expression(this);
}

void ReentPreParser::Xpath_plus_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitXpath_plus_expression(this);
}

ReentPreParser::Xpath_plus_expressionContext* ReentPreParser::xpath_plus_expression() {
  Xpath_plus_expressionContext *_localctx = _tracker.createInstance<Xpath_plus_expressionContext>(_ctx, getState());
  enterRule(_localctx, 20, ReentPreParser::RuleXpath_plus_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(357);
    xpath_unary_expression();
    setState(362);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Plus

    || _la == ReentPreParser::Minus) {
      setState(358);
      _la = _input->LA(1);
      if (!(_la == ReentPreParser::Plus

      || _la == ReentPreParser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(359);
      xpath_unary_expression();
      setState(364);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Xpath_unary_expressionContext ------------------------------------------------------------------

ReentPreParser::Xpath_unary_expressionContext::Xpath_unary_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Xpath_unary_expressionContext::StringLiteral() {
  return getToken(ReentPreParser::StringLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Xpath_unary_expressionContext::CharacterLiteral() {
  return getToken(ReentPreParser::CharacterLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Xpath_unary_expressionContext::EmptyAtom() {
  return getToken(ReentPreParser::EmptyAtom, 0);
}

tree::TerminalNode* ReentPreParser::Xpath_unary_expressionContext::IntegerLiteral() {
  return getToken(ReentPreParser::IntegerLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Xpath_unary_expressionContext::FloatingLiteral() {
  return getToken(ReentPreParser::FloatingLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Xpath_unary_expressionContext::AtValue() {
  return getToken(ReentPreParser::AtValue, 0);
}

tree::TerminalNode* ReentPreParser::Xpath_unary_expressionContext::GetText() {
  return getToken(ReentPreParser::GetText, 0);
}

tree::TerminalNode* ReentPreParser::Xpath_unary_expressionContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

ReentPreParser::Simple_xpath_expressionContext* ReentPreParser::Xpath_unary_expressionContext::simple_xpath_expression() {
  return getRuleContext<ReentPreParser::Simple_xpath_expressionContext>(0);
}

tree::TerminalNode* ReentPreParser::Xpath_unary_expressionContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

ReentPreParser::Xpath_queryContext* ReentPreParser::Xpath_unary_expressionContext::xpath_query() {
  return getRuleContext<ReentPreParser::Xpath_queryContext>(0);
}

tree::TerminalNode* ReentPreParser::Xpath_unary_expressionContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

ReentPreParser::Xpath_fun_paramsContext* ReentPreParser::Xpath_unary_expressionContext::xpath_fun_params() {
  return getRuleContext<ReentPreParser::Xpath_fun_paramsContext>(0);
}


size_t ReentPreParser::Xpath_unary_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleXpath_unary_expression;
}

void ReentPreParser::Xpath_unary_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterXpath_unary_expression(this);
}

void ReentPreParser::Xpath_unary_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitXpath_unary_expression(this);
}

ReentPreParser::Xpath_unary_expressionContext* ReentPreParser::xpath_unary_expression() {
  Xpath_unary_expressionContext *_localctx = _tracker.createInstance<Xpath_unary_expressionContext>(_ctx, getState());
  enterRule(_localctx, 22, ReentPreParser::RuleXpath_unary_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(385);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(365);
      match(ReentPreParser::StringLiteral);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(366);
      match(ReentPreParser::CharacterLiteral);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(367);
      match(ReentPreParser::EmptyAtom);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(368);
      match(ReentPreParser::IntegerLiteral);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(369);
      match(ReentPreParser::FloatingLiteral);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(370);
      match(ReentPreParser::AtValue);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(371);
      match(ReentPreParser::GetText);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(372);
      match(ReentPreParser::LeftParen);
      setState(373);
      simple_xpath_expression();
      setState(374);
      match(ReentPreParser::RightParen);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(376);
      xpath_query();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(377);
      match(ReentPreParser::Identifier);
      setState(383);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::LeftParen) {
        setState(378);
        match(ReentPreParser::LeftParen);
        setState(380);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << ReentPreParser::IntegerLiteral)
          | (1ULL << ReentPreParser::CharacterLiteral)
          | (1ULL << ReentPreParser::FloatingLiteral)
          | (1ULL << ReentPreParser::StringLiteral)
          | (1ULL << ReentPreParser::EmptyAtom)
          | (1ULL << ReentPreParser::AtValue)
          | (1ULL << ReentPreParser::GetText)
          | (1ULL << ReentPreParser::LeftParen)
          | (1ULL << ReentPreParser::DivDiv))) != 0) || ((((_la - 75) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 75)) & ((1ULL << (ReentPreParser::Star - 75))
          | (1ULL << (ReentPreParser::Div - 75))
          | (1ULL << (ReentPreParser::Identifier - 75)))) != 0)) {
          setState(379);
          xpath_fun_params();
        }
        setState(382);
        match(ReentPreParser::RightParen);
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Xpath_queryContext ------------------------------------------------------------------

ReentPreParser::Xpath_queryContext::Xpath_queryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_queryContext::Div() {
  return getTokens(ReentPreParser::Div);
}

tree::TerminalNode* ReentPreParser::Xpath_queryContext::Div(size_t i) {
  return getToken(ReentPreParser::Div, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_queryContext::DivDiv() {
  return getTokens(ReentPreParser::DivDiv);
}

tree::TerminalNode* ReentPreParser::Xpath_queryContext::DivDiv(size_t i) {
  return getToken(ReentPreParser::DivDiv, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_queryContext::Star() {
  return getTokens(ReentPreParser::Star);
}

tree::TerminalNode* ReentPreParser::Xpath_queryContext::Star(size_t i) {
  return getToken(ReentPreParser::Star, i);
}

tree::TerminalNode* ReentPreParser::Xpath_queryContext::AtValue() {
  return getToken(ReentPreParser::AtValue, 0);
}

tree::TerminalNode* ReentPreParser::Xpath_queryContext::GetText() {
  return getToken(ReentPreParser::GetText, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_queryContext::Identifier() {
  return getTokens(ReentPreParser::Identifier);
}

tree::TerminalNode* ReentPreParser::Xpath_queryContext::Identifier(size_t i) {
  return getToken(ReentPreParser::Identifier, i);
}

std::vector<ReentPreParser::Xpath_predicateContext *> ReentPreParser::Xpath_queryContext::xpath_predicate() {
  return getRuleContexts<ReentPreParser::Xpath_predicateContext>();
}

ReentPreParser::Xpath_predicateContext* ReentPreParser::Xpath_queryContext::xpath_predicate(size_t i) {
  return getRuleContext<ReentPreParser::Xpath_predicateContext>(i);
}


size_t ReentPreParser::Xpath_queryContext::getRuleIndex() const {
  return ReentPreParser::RuleXpath_query;
}

void ReentPreParser::Xpath_queryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterXpath_query(this);
}

void ReentPreParser::Xpath_queryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitXpath_query(this);
}

ReentPreParser::Xpath_queryContext* ReentPreParser::xpath_query() {
  Xpath_queryContext *_localctx = _tracker.createInstance<Xpath_queryContext>(_ctx, getState());
  enterRule(_localctx, 24, ReentPreParser::RuleXpath_query);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(388);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::DivDiv

    || _la == ReentPreParser::Div) {
      setState(387);
      _la = _input->LA(1);
      if (!(_la == ReentPreParser::DivDiv

      || _la == ReentPreParser::Div)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(393);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Identifier: {
        setState(390);
        dynamic_cast<Xpath_queryContext *>(_localctx)->var = match(ReentPreParser::Identifier);
         regexp_refs.insert((dynamic_cast<Xpath_queryContext *>(_localctx)->var != nullptr ? dynamic_cast<Xpath_queryContext *>(_localctx)->var->getText() : "")); 
        break;
      }

      case ReentPreParser::Star: {
        setState(392);
        match(ReentPreParser::Star);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(396);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftBracket) {
      setState(395);
      xpath_predicate();
    }
    setState(409);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(398);
        _la = _input->LA(1);
        if (!(_la == ReentPreParser::DivDiv

        || _la == ReentPreParser::Div)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(402);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case ReentPreParser::Identifier: {
            setState(399);
            dynamic_cast<Xpath_queryContext *>(_localctx)->next = match(ReentPreParser::Identifier);
             regexp_refs.insert((dynamic_cast<Xpath_queryContext *>(_localctx)->next != nullptr ? dynamic_cast<Xpath_queryContext *>(_localctx)->next->getText() : "")); 
            break;
          }

          case ReentPreParser::Star: {
            setState(401);
            match(ReentPreParser::Star);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(405);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::LeftBracket) {
          setState(404);
          xpath_predicate();
        } 
      }
      setState(411);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    }
    setState(412);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::DivDiv

    || _la == ReentPreParser::Div)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(420);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Star:
      case ReentPreParser::Identifier: {
        setState(416);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case ReentPreParser::Identifier: {
            setState(413);
            dynamic_cast<Xpath_queryContext *>(_localctx)->last = match(ReentPreParser::Identifier);
             regexp_refs.insert((dynamic_cast<Xpath_queryContext *>(_localctx)->last != nullptr ? dynamic_cast<Xpath_queryContext *>(_localctx)->last->getText() : "")); 
            break;
          }

          case ReentPreParser::Star: {
            setState(415);
            match(ReentPreParser::Star);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

      case ReentPreParser::AtValue: {
        setState(418);
        match(ReentPreParser::AtValue);
        break;
      }

      case ReentPreParser::GetText: {
        setState(419);
        match(ReentPreParser::GetText);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Xpath_predicateContext ------------------------------------------------------------------

ReentPreParser::Xpath_predicateContext::Xpath_predicateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Xpath_predicateContext::LeftBracket() {
  return getToken(ReentPreParser::LeftBracket, 0);
}

ReentPreParser::Simple_xpath_expressionContext* ReentPreParser::Xpath_predicateContext::simple_xpath_expression() {
  return getRuleContext<ReentPreParser::Simple_xpath_expressionContext>(0);
}

tree::TerminalNode* ReentPreParser::Xpath_predicateContext::RightBracket() {
  return getToken(ReentPreParser::RightBracket, 0);
}


size_t ReentPreParser::Xpath_predicateContext::getRuleIndex() const {
  return ReentPreParser::RuleXpath_predicate;
}

void ReentPreParser::Xpath_predicateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterXpath_predicate(this);
}

void ReentPreParser::Xpath_predicateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitXpath_predicate(this);
}

ReentPreParser::Xpath_predicateContext* ReentPreParser::xpath_predicate() {
  Xpath_predicateContext *_localctx = _tracker.createInstance<Xpath_predicateContext>(_ctx, getState());
  enterRule(_localctx, 26, ReentPreParser::RuleXpath_predicate);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(422);
    match(ReentPreParser::LeftBracket);
    setState(423);
    simple_xpath_expression();
    setState(424);
    match(ReentPreParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Xpath_fun_paramsContext ------------------------------------------------------------------

ReentPreParser::Xpath_fun_paramsContext::Xpath_fun_paramsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Simple_xpath_expressionContext *> ReentPreParser::Xpath_fun_paramsContext::simple_xpath_expression() {
  return getRuleContexts<ReentPreParser::Simple_xpath_expressionContext>();
}

ReentPreParser::Simple_xpath_expressionContext* ReentPreParser::Xpath_fun_paramsContext::simple_xpath_expression(size_t i) {
  return getRuleContext<ReentPreParser::Simple_xpath_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Xpath_fun_paramsContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Xpath_fun_paramsContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::Xpath_fun_paramsContext::getRuleIndex() const {
  return ReentPreParser::RuleXpath_fun_params;
}

void ReentPreParser::Xpath_fun_paramsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterXpath_fun_params(this);
}

void ReentPreParser::Xpath_fun_paramsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitXpath_fun_params(this);
}

ReentPreParser::Xpath_fun_paramsContext* ReentPreParser::xpath_fun_params() {
  Xpath_fun_paramsContext *_localctx = _tracker.createInstance<Xpath_fun_paramsContext>(_ctx, getState());
  enterRule(_localctx, 28, ReentPreParser::RuleXpath_fun_params);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(426);
    simple_xpath_expression();
    setState(431);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(427);
      match(ReentPreParser::Comma);
      setState(428);
      simple_xpath_expression();
      setState(433);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_xpathContext ------------------------------------------------------------------

ReentPreParser::Def_xpathContext::Def_xpathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Def_xpathContext::DefXPath() {
  return getToken(ReentPreParser::DefXPath, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpathContext::LeftBrace() {
  return getToken(ReentPreParser::LeftBrace, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpathContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Def_xpathContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

ReentPreParser::Def_xpath_expressionContext* ReentPreParser::Def_xpathContext::def_xpath_expression() {
  return getRuleContext<ReentPreParser::Def_xpath_expressionContext>(0);
}

tree::TerminalNode* ReentPreParser::Def_xpathContext::RightBrace() {
  return getToken(ReentPreParser::RightBrace, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpathContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpathContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpathContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

std::vector<ReentPreParser::Def_xpath_paramContext *> ReentPreParser::Def_xpathContext::def_xpath_param() {
  return getRuleContexts<ReentPreParser::Def_xpath_paramContext>();
}

ReentPreParser::Def_xpath_paramContext* ReentPreParser::Def_xpathContext::def_xpath_param(size_t i) {
  return getRuleContext<ReentPreParser::Def_xpath_paramContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpathContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Def_xpathContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::Def_xpathContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_xpath;
}

void ReentPreParser::Def_xpathContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_xpath(this);
}

void ReentPreParser::Def_xpathContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_xpath(this);
}

ReentPreParser::Def_xpathContext* ReentPreParser::def_xpath() {
  Def_xpathContext *_localctx = _tracker.createInstance<Def_xpathContext>(_ctx, getState());
  enterRule(_localctx, 30, ReentPreParser::RuleDef_xpath);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(434);
    match(ReentPreParser::DefXPath);
    setState(435);
    dynamic_cast<Def_xpathContext *>(_localctx)->id = match(ReentPreParser::Identifier);

    		if (xpaths.find((dynamic_cast<Def_xpathContext *>(_localctx)->id != nullptr ? dynamic_cast<Def_xpathContext *>(_localctx)->id->getText() : "")) != xpaths.end())
    			throw FailedPredicateException(this, "XPath is already defined");
    		xpaths.insert((dynamic_cast<Def_xpathContext *>(_localctx)->id != nullptr ? dynamic_cast<Def_xpathContext *>(_localctx)->id->getText() : ""));
    	
    setState(449);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftParen) {
      setState(437);
      match(ReentPreParser::LeftParen);
      setState(446);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Regexp_ref

      || _la == ReentPreParser::And) {
        setState(438);
        def_xpath_param();
        setState(443);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ReentPreParser::Comma) {
          setState(439);
          match(ReentPreParser::Comma);
          setState(440);
          def_xpath_param();
          setState(445);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(448);
      match(ReentPreParser::RightParen);
    }
    setState(451);
    match(ReentPreParser::LeftBrace);
    setState(452);
    match(ReentPreParser::Newline);
    setState(453);
    def_xpath_expression();
    setState(454);
    match(ReentPreParser::RightBrace);
    setState(455);
    match(ReentPreParser::Newline);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_xpath_paramContext ------------------------------------------------------------------

ReentPreParser::Def_xpath_paramContext::Def_xpath_paramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Def_xpath_paramContext::Regexp_ref() {
  return getToken(ReentPreParser::Regexp_ref, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_paramContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_paramContext::And() {
  return getToken(ReentPreParser::And, 0);
}


size_t ReentPreParser::Def_xpath_paramContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_xpath_param;
}

void ReentPreParser::Def_xpath_paramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_xpath_param(this);
}

void ReentPreParser::Def_xpath_paramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_xpath_param(this);
}

ReentPreParser::Def_xpath_paramContext* ReentPreParser::def_xpath_param() {
  Def_xpath_paramContext *_localctx = _tracker.createInstance<Def_xpath_paramContext>(_ctx, getState());
  enterRule(_localctx, 32, ReentPreParser::RuleDef_xpath_param);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(458);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::And) {
      setState(457);
      match(ReentPreParser::And);
    }
    setState(460);
    match(ReentPreParser::Regexp_ref);
    setState(461);
    match(ReentPreParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_xpath_expressionContext ------------------------------------------------------------------

ReentPreParser::Def_xpath_expressionContext::Def_xpath_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Def_xpath_and_expressionContext *> ReentPreParser::Def_xpath_expressionContext::def_xpath_and_expression() {
  return getRuleContexts<ReentPreParser::Def_xpath_and_expressionContext>();
}

ReentPreParser::Def_xpath_and_expressionContext* ReentPreParser::Def_xpath_expressionContext::def_xpath_and_expression(size_t i) {
  return getRuleContext<ReentPreParser::Def_xpath_and_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_expressionContext::Or_() {
  return getTokens(ReentPreParser::Or_);
}

tree::TerminalNode* ReentPreParser::Def_xpath_expressionContext::Or_(size_t i) {
  return getToken(ReentPreParser::Or_, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_expressionContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Def_xpath_expressionContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}


size_t ReentPreParser::Def_xpath_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_xpath_expression;
}

void ReentPreParser::Def_xpath_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_xpath_expression(this);
}

void ReentPreParser::Def_xpath_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_xpath_expression(this);
}

ReentPreParser::Def_xpath_expressionContext* ReentPreParser::def_xpath_expression() {
  Def_xpath_expressionContext *_localctx = _tracker.createInstance<Def_xpath_expressionContext>(_ctx, getState());
  enterRule(_localctx, 34, ReentPreParser::RuleDef_xpath_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(463);
    def_xpath_and_expression();
    setState(474);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(465);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(464);
          match(ReentPreParser::Newline);
        }
        setState(467);
        match(ReentPreParser::Or_);
        setState(469);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
        case 1: {
          setState(468);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(471);
        def_xpath_and_expression(); 
      }
      setState(476);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    }
    setState(478);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx)) {
    case 1: {
      setState(477);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_xpath_and_expressionContext ------------------------------------------------------------------

ReentPreParser::Def_xpath_and_expressionContext::Def_xpath_and_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Def_xpath_rel_expressionContext *> ReentPreParser::Def_xpath_and_expressionContext::def_xpath_rel_expression() {
  return getRuleContexts<ReentPreParser::Def_xpath_rel_expressionContext>();
}

ReentPreParser::Def_xpath_rel_expressionContext* ReentPreParser::Def_xpath_and_expressionContext::def_xpath_rel_expression(size_t i) {
  return getRuleContext<ReentPreParser::Def_xpath_rel_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_and_expressionContext::And_() {
  return getTokens(ReentPreParser::And_);
}

tree::TerminalNode* ReentPreParser::Def_xpath_and_expressionContext::And_(size_t i) {
  return getToken(ReentPreParser::And_, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_and_expressionContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Def_xpath_and_expressionContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}


size_t ReentPreParser::Def_xpath_and_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_xpath_and_expression;
}

void ReentPreParser::Def_xpath_and_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_xpath_and_expression(this);
}

void ReentPreParser::Def_xpath_and_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_xpath_and_expression(this);
}

ReentPreParser::Def_xpath_and_expressionContext* ReentPreParser::def_xpath_and_expression() {
  Def_xpath_and_expressionContext *_localctx = _tracker.createInstance<Def_xpath_and_expressionContext>(_ctx, getState());
  enterRule(_localctx, 36, ReentPreParser::RuleDef_xpath_and_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(480);
    def_xpath_rel_expression();
    setState(491);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(482);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(481);
          match(ReentPreParser::Newline);
        }
        setState(484);
        match(ReentPreParser::And_);
        setState(486);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 39, _ctx)) {
        case 1: {
          setState(485);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(488);
        def_xpath_rel_expression(); 
      }
      setState(493);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    }
    setState(495);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx)) {
    case 1: {
      setState(494);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_xpath_rel_expressionContext ------------------------------------------------------------------

ReentPreParser::Def_xpath_rel_expressionContext::Def_xpath_rel_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Def_xpath_mul_expressionContext *> ReentPreParser::Def_xpath_rel_expressionContext::def_xpath_mul_expression() {
  return getRuleContexts<ReentPreParser::Def_xpath_mul_expressionContext>();
}

ReentPreParser::Def_xpath_mul_expressionContext* ReentPreParser::Def_xpath_rel_expressionContext::def_xpath_mul_expression(size_t i) {
  return getRuleContext<ReentPreParser::Def_xpath_mul_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_rel_expressionContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Def_xpath_rel_expressionContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_rel_expressionContext::Less() {
  return getTokens(ReentPreParser::Less);
}

tree::TerminalNode* ReentPreParser::Def_xpath_rel_expressionContext::Less(size_t i) {
  return getToken(ReentPreParser::Less, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_rel_expressionContext::Greater() {
  return getTokens(ReentPreParser::Greater);
}

tree::TerminalNode* ReentPreParser::Def_xpath_rel_expressionContext::Greater(size_t i) {
  return getToken(ReentPreParser::Greater, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_rel_expressionContext::Assign() {
  return getTokens(ReentPreParser::Assign);
}

tree::TerminalNode* ReentPreParser::Def_xpath_rel_expressionContext::Assign(size_t i) {
  return getToken(ReentPreParser::Assign, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_rel_expressionContext::NotEqual() {
  return getTokens(ReentPreParser::NotEqual);
}

tree::TerminalNode* ReentPreParser::Def_xpath_rel_expressionContext::NotEqual(size_t i) {
  return getToken(ReentPreParser::NotEqual, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_rel_expressionContext::LessEqual() {
  return getTokens(ReentPreParser::LessEqual);
}

tree::TerminalNode* ReentPreParser::Def_xpath_rel_expressionContext::LessEqual(size_t i) {
  return getToken(ReentPreParser::LessEqual, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_rel_expressionContext::GreaterEqual() {
  return getTokens(ReentPreParser::GreaterEqual);
}

tree::TerminalNode* ReentPreParser::Def_xpath_rel_expressionContext::GreaterEqual(size_t i) {
  return getToken(ReentPreParser::GreaterEqual, i);
}


size_t ReentPreParser::Def_xpath_rel_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_xpath_rel_expression;
}

void ReentPreParser::Def_xpath_rel_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_xpath_rel_expression(this);
}

void ReentPreParser::Def_xpath_rel_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_xpath_rel_expression(this);
}

ReentPreParser::Def_xpath_rel_expressionContext* ReentPreParser::def_xpath_rel_expression() {
  Def_xpath_rel_expressionContext *_localctx = _tracker.createInstance<Def_xpath_rel_expressionContext>(_ctx, getState());
  enterRule(_localctx, 38, ReentPreParser::RuleDef_xpath_rel_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(497);
    def_xpath_mul_expression();
    setState(508);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(499);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(498);
          match(ReentPreParser::Newline);
        }
        setState(501);
        _la = _input->LA(1);
        if (!(((((_la - 83) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 83)) & ((1ULL << (ReentPreParser::Assign - 83))
          | (1ULL << (ReentPreParser::Less - 83))
          | (1ULL << (ReentPreParser::Greater - 83))
          | (1ULL << (ReentPreParser::NotEqual - 83))
          | (1ULL << (ReentPreParser::LessEqual - 83))
          | (1ULL << (ReentPreParser::GreaterEqual - 83)))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(503);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 43, _ctx)) {
        case 1: {
          setState(502);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(505);
        def_xpath_mul_expression(); 
      }
      setState(510);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx);
    }
    setState(512);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx)) {
    case 1: {
      setState(511);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_xpath_mul_expressionContext ------------------------------------------------------------------

ReentPreParser::Def_xpath_mul_expressionContext::Def_xpath_mul_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Def_xpath_plus_expressionContext *> ReentPreParser::Def_xpath_mul_expressionContext::def_xpath_plus_expression() {
  return getRuleContexts<ReentPreParser::Def_xpath_plus_expressionContext>();
}

ReentPreParser::Def_xpath_plus_expressionContext* ReentPreParser::Def_xpath_mul_expressionContext::def_xpath_plus_expression(size_t i) {
  return getRuleContext<ReentPreParser::Def_xpath_plus_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_mul_expressionContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Def_xpath_mul_expressionContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_mul_expressionContext::Star() {
  return getTokens(ReentPreParser::Star);
}

tree::TerminalNode* ReentPreParser::Def_xpath_mul_expressionContext::Star(size_t i) {
  return getToken(ReentPreParser::Star, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_mul_expressionContext::Div() {
  return getTokens(ReentPreParser::Div);
}

tree::TerminalNode* ReentPreParser::Def_xpath_mul_expressionContext::Div(size_t i) {
  return getToken(ReentPreParser::Div, i);
}


size_t ReentPreParser::Def_xpath_mul_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_xpath_mul_expression;
}

void ReentPreParser::Def_xpath_mul_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_xpath_mul_expression(this);
}

void ReentPreParser::Def_xpath_mul_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_xpath_mul_expression(this);
}

ReentPreParser::Def_xpath_mul_expressionContext* ReentPreParser::def_xpath_mul_expression() {
  Def_xpath_mul_expressionContext *_localctx = _tracker.createInstance<Def_xpath_mul_expressionContext>(_ctx, getState());
  enterRule(_localctx, 40, ReentPreParser::RuleDef_xpath_mul_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(514);
    def_xpath_plus_expression();
    setState(525);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(516);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(515);
          match(ReentPreParser::Newline);
        }
        setState(518);
        _la = _input->LA(1);
        if (!(_la == ReentPreParser::Star

        || _la == ReentPreParser::Div)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(520);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx)) {
        case 1: {
          setState(519);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(522);
        def_xpath_plus_expression(); 
      }
      setState(527);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx);
    }
    setState(529);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx)) {
    case 1: {
      setState(528);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_xpath_plus_expressionContext ------------------------------------------------------------------

ReentPreParser::Def_xpath_plus_expressionContext::Def_xpath_plus_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Def_xpath_unary_expressionContext *> ReentPreParser::Def_xpath_plus_expressionContext::def_xpath_unary_expression() {
  return getRuleContexts<ReentPreParser::Def_xpath_unary_expressionContext>();
}

ReentPreParser::Def_xpath_unary_expressionContext* ReentPreParser::Def_xpath_plus_expressionContext::def_xpath_unary_expression(size_t i) {
  return getRuleContext<ReentPreParser::Def_xpath_unary_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_plus_expressionContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Def_xpath_plus_expressionContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_plus_expressionContext::Plus() {
  return getTokens(ReentPreParser::Plus);
}

tree::TerminalNode* ReentPreParser::Def_xpath_plus_expressionContext::Plus(size_t i) {
  return getToken(ReentPreParser::Plus, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_plus_expressionContext::Minus() {
  return getTokens(ReentPreParser::Minus);
}

tree::TerminalNode* ReentPreParser::Def_xpath_plus_expressionContext::Minus(size_t i) {
  return getToken(ReentPreParser::Minus, i);
}


size_t ReentPreParser::Def_xpath_plus_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_xpath_plus_expression;
}

void ReentPreParser::Def_xpath_plus_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_xpath_plus_expression(this);
}

void ReentPreParser::Def_xpath_plus_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_xpath_plus_expression(this);
}

ReentPreParser::Def_xpath_plus_expressionContext* ReentPreParser::def_xpath_plus_expression() {
  Def_xpath_plus_expressionContext *_localctx = _tracker.createInstance<Def_xpath_plus_expressionContext>(_ctx, getState());
  enterRule(_localctx, 42, ReentPreParser::RuleDef_xpath_plus_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(531);
    def_xpath_unary_expression();
    setState(542);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(533);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(532);
          match(ReentPreParser::Newline);
        }
        setState(535);
        _la = _input->LA(1);
        if (!(_la == ReentPreParser::Plus

        || _la == ReentPreParser::Minus)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(537);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
        case 1: {
          setState(536);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(539);
        def_xpath_unary_expression(); 
      }
      setState(544);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 52, _ctx);
    }
    setState(546);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
    case 1: {
      setState(545);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_xpath_unary_expressionContext ------------------------------------------------------------------

ReentPreParser::Def_xpath_unary_expressionContext::Def_xpath_unary_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::StringLiteral() {
  return getToken(ReentPreParser::StringLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::CharacterLiteral() {
  return getToken(ReentPreParser::CharacterLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::EmptyAtom() {
  return getToken(ReentPreParser::EmptyAtom, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::IntegerLiteral() {
  return getToken(ReentPreParser::IntegerLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::FloatingLiteral() {
  return getToken(ReentPreParser::FloatingLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::AtValue() {
  return getToken(ReentPreParser::AtValue, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::At() {
  return getToken(ReentPreParser::At, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::GetText() {
  return getToken(ReentPreParser::GetText, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

ReentPreParser::Def_xpath_expressionContext* ReentPreParser::Def_xpath_unary_expressionContext::def_xpath_expression() {
  return getRuleContext<ReentPreParser::Def_xpath_expressionContext>(0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_unary_expressionContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

ReentPreParser::Def_xpath_fun_paramsContext* ReentPreParser::Def_xpath_unary_expressionContext::def_xpath_fun_params() {
  return getRuleContext<ReentPreParser::Def_xpath_fun_paramsContext>(0);
}

ReentPreParser::Def_xpath_queryContext* ReentPreParser::Def_xpath_unary_expressionContext::def_xpath_query() {
  return getRuleContext<ReentPreParser::Def_xpath_queryContext>(0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_unary_expressionContext::Regexp_ref() {
  return getToken(ReentPreParser::Regexp_ref, 0);
}


size_t ReentPreParser::Def_xpath_unary_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_xpath_unary_expression;
}

void ReentPreParser::Def_xpath_unary_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_xpath_unary_expression(this);
}

void ReentPreParser::Def_xpath_unary_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_xpath_unary_expression(this);
}

ReentPreParser::Def_xpath_unary_expressionContext* ReentPreParser::def_xpath_unary_expression() {
  Def_xpath_unary_expressionContext *_localctx = _tracker.createInstance<Def_xpath_unary_expressionContext>(_ctx, getState());
  enterRule(_localctx, 44, ReentPreParser::RuleDef_xpath_unary_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(593);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(548);
      match(ReentPreParser::StringLiteral);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(549);
      match(ReentPreParser::CharacterLiteral);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(550);
      match(ReentPreParser::EmptyAtom);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(551);
      match(ReentPreParser::IntegerLiteral);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(552);
      match(ReentPreParser::FloatingLiteral);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(553);
      match(ReentPreParser::AtValue);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(554);
      match(ReentPreParser::At);
      setState(555);
      match(ReentPreParser::Identifier);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(556);
      match(ReentPreParser::GetText);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(557);
      match(ReentPreParser::LeftParen);
      setState(559);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
      case 1: {
        setState(558);
        match(ReentPreParser::Newline);
        break;
      }

      default:
        break;
      }
      setState(561);
      def_xpath_expression();
      setState(563);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(562);
        match(ReentPreParser::Newline);
      }
      setState(565);
      match(ReentPreParser::RightParen);
      setState(567);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
      case 1: {
        setState(566);
        match(ReentPreParser::Newline);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(569);
      match(ReentPreParser::Identifier);
      setState(571);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(570);
        match(ReentPreParser::Newline);
      }
      setState(573);
      match(ReentPreParser::LeftParen);
      setState(575);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
      case 1: {
        setState(574);
        match(ReentPreParser::Newline);
        break;
      }

      default:
        break;
      }
      setState(578);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
      case 1: {
        setState(577);
        def_xpath_fun_params();
        break;
      }

      default:
        break;
      }
      setState(581);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(580);
        match(ReentPreParser::Newline);
      }
      setState(583);
      match(ReentPreParser::RightParen);
      setState(585);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 61, _ctx)) {
      case 1: {
        setState(584);
        match(ReentPreParser::Newline);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(587);
      def_xpath_query();
      setState(589);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 62, _ctx)) {
      case 1: {
        setState(588);
        match(ReentPreParser::Newline);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(591);
      match(ReentPreParser::Regexp_ref);
      setState(592);
      match(ReentPreParser::Identifier);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_xpath_queryContext ------------------------------------------------------------------

ReentPreParser::Def_xpath_queryContext::Def_xpath_queryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_queryContext::Identifier() {
  return getTokens(ReentPreParser::Identifier);
}

tree::TerminalNode* ReentPreParser::Def_xpath_queryContext::Identifier(size_t i) {
  return getToken(ReentPreParser::Identifier, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_queryContext::Star() {
  return getTokens(ReentPreParser::Star);
}

tree::TerminalNode* ReentPreParser::Def_xpath_queryContext::Star(size_t i) {
  return getToken(ReentPreParser::Star, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_queryContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Def_xpath_queryContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

std::vector<ReentPreParser::Def_xpath_predicateContext *> ReentPreParser::Def_xpath_queryContext::def_xpath_predicate() {
  return getRuleContexts<ReentPreParser::Def_xpath_predicateContext>();
}

ReentPreParser::Def_xpath_predicateContext* ReentPreParser::Def_xpath_queryContext::def_xpath_predicate(size_t i) {
  return getRuleContext<ReentPreParser::Def_xpath_predicateContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_queryContext::Div() {
  return getTokens(ReentPreParser::Div);
}

tree::TerminalNode* ReentPreParser::Def_xpath_queryContext::Div(size_t i) {
  return getToken(ReentPreParser::Div, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_queryContext::DivDiv() {
  return getTokens(ReentPreParser::DivDiv);
}

tree::TerminalNode* ReentPreParser::Def_xpath_queryContext::DivDiv(size_t i) {
  return getToken(ReentPreParser::DivDiv, i);
}

tree::TerminalNode* ReentPreParser::Def_xpath_queryContext::AtValue() {
  return getToken(ReentPreParser::AtValue, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_queryContext::At() {
  return getToken(ReentPreParser::At, 0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_queryContext::GetText() {
  return getToken(ReentPreParser::GetText, 0);
}


size_t ReentPreParser::Def_xpath_queryContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_xpath_query;
}

void ReentPreParser::Def_xpath_queryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_xpath_query(this);
}

void ReentPreParser::Def_xpath_queryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_xpath_query(this);
}

ReentPreParser::Def_xpath_queryContext* ReentPreParser::def_xpath_query() {
  Def_xpath_queryContext *_localctx = _tracker.createInstance<Def_xpath_queryContext>(_ctx, getState());
  enterRule(_localctx, 46, ReentPreParser::RuleDef_xpath_query);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(596);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::DivDiv

    || _la == ReentPreParser::Div) {
      setState(595);
      _la = _input->LA(1);
      if (!(_la == ReentPreParser::DivDiv

      || _la == ReentPreParser::Div)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(599);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Newline) {
      setState(598);
      match(ReentPreParser::Newline);
    }
    setState(601);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::Star

    || _la == ReentPreParser::Identifier)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(603);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
    case 1: {
      setState(602);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(606);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftBracket) {
      setState(605);
      def_xpath_predicate();
    }
    setState(621);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(608);
        _la = _input->LA(1);
        if (!(_la == ReentPreParser::DivDiv

        || _la == ReentPreParser::Div)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(610);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(609);
          match(ReentPreParser::Newline);
        }
        setState(612);
        _la = _input->LA(1);
        if (!(_la == ReentPreParser::Star

        || _la == ReentPreParser::Identifier)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(614);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
        case 1: {
          setState(613);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(617);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::LeftBracket) {
          setState(616);
          def_xpath_predicate();
        } 
      }
      setState(623);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx);
    }
    setState(635);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      setState(624);
      _la = _input->LA(1);
      if (!(_la == ReentPreParser::DivDiv

      || _la == ReentPreParser::Div)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(626);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(625);
        match(ReentPreParser::Newline);
      }
      setState(633);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case ReentPreParser::Star:
        case ReentPreParser::Identifier: {
          setState(628);
          _la = _input->LA(1);
          if (!(_la == ReentPreParser::Star

          || _la == ReentPreParser::Identifier)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        case ReentPreParser::AtValue: {
          setState(629);
          match(ReentPreParser::AtValue);
          break;
        }

        case ReentPreParser::At: {
          setState(630);
          match(ReentPreParser::At);
          setState(631);
          match(ReentPreParser::Identifier);
          break;
        }

        case ReentPreParser::GetText: {
          setState(632);
          match(ReentPreParser::GetText);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_xpath_predicateContext ------------------------------------------------------------------

ReentPreParser::Def_xpath_predicateContext::Def_xpath_predicateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Def_xpath_predicateContext::LeftBracket() {
  return getToken(ReentPreParser::LeftBracket, 0);
}

ReentPreParser::Def_xpath_expressionContext* ReentPreParser::Def_xpath_predicateContext::def_xpath_expression() {
  return getRuleContext<ReentPreParser::Def_xpath_expressionContext>(0);
}

tree::TerminalNode* ReentPreParser::Def_xpath_predicateContext::RightBracket() {
  return getToken(ReentPreParser::RightBracket, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_predicateContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Def_xpath_predicateContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}


size_t ReentPreParser::Def_xpath_predicateContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_xpath_predicate;
}

void ReentPreParser::Def_xpath_predicateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_xpath_predicate(this);
}

void ReentPreParser::Def_xpath_predicateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_xpath_predicate(this);
}

ReentPreParser::Def_xpath_predicateContext* ReentPreParser::def_xpath_predicate() {
  Def_xpath_predicateContext *_localctx = _tracker.createInstance<Def_xpath_predicateContext>(_ctx, getState());
  enterRule(_localctx, 48, ReentPreParser::RuleDef_xpath_predicate);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(637);
    match(ReentPreParser::LeftBracket);
    setState(639);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx)) {
    case 1: {
      setState(638);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(641);
    def_xpath_expression();
    setState(643);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Newline) {
      setState(642);
      match(ReentPreParser::Newline);
    }
    setState(645);
    match(ReentPreParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Def_xpath_fun_paramsContext ------------------------------------------------------------------

ReentPreParser::Def_xpath_fun_paramsContext::Def_xpath_fun_paramsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Def_xpath_expressionContext *> ReentPreParser::Def_xpath_fun_paramsContext::def_xpath_expression() {
  return getRuleContexts<ReentPreParser::Def_xpath_expressionContext>();
}

ReentPreParser::Def_xpath_expressionContext* ReentPreParser::Def_xpath_fun_paramsContext::def_xpath_expression(size_t i) {
  return getRuleContext<ReentPreParser::Def_xpath_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_fun_paramsContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Def_xpath_fun_paramsContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Def_xpath_fun_paramsContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Def_xpath_fun_paramsContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}


size_t ReentPreParser::Def_xpath_fun_paramsContext::getRuleIndex() const {
  return ReentPreParser::RuleDef_xpath_fun_params;
}

void ReentPreParser::Def_xpath_fun_paramsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDef_xpath_fun_params(this);
}

void ReentPreParser::Def_xpath_fun_paramsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDef_xpath_fun_params(this);
}

ReentPreParser::Def_xpath_fun_paramsContext* ReentPreParser::def_xpath_fun_params() {
  Def_xpath_fun_paramsContext *_localctx = _tracker.createInstance<Def_xpath_fun_paramsContext>(_ctx, getState());
  enterRule(_localctx, 50, ReentPreParser::RuleDef_xpath_fun_params);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(647);
    def_xpath_expression();
    setState(658);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(649);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(648);
          match(ReentPreParser::Newline);
        }
        setState(651);
        match(ReentPreParser::Comma);
        setState(653);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx)) {
        case 1: {
          setState(652);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(655);
        def_xpath_expression(); 
      }
      setState(660);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
    }
    setState(662);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 80, _ctx)) {
    case 1: {
      setState(661);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RegexpsContext ------------------------------------------------------------------

ReentPreParser::RegexpsContext::RegexpsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::RegexpsContext::LeftBrace() {
  return getToken(ReentPreParser::LeftBrace, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::RegexpsContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::RegexpsContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

tree::TerminalNode* ReentPreParser::RegexpsContext::RightBrace() {
  return getToken(ReentPreParser::RightBrace, 0);
}

tree::TerminalNode* ReentPreParser::RegexpsContext::Semi() {
  return getToken(ReentPreParser::Semi, 0);
}

std::vector<ReentPreParser::Regexp_linesContext *> ReentPreParser::RegexpsContext::regexp_lines() {
  return getRuleContexts<ReentPreParser::Regexp_linesContext>();
}

ReentPreParser::Regexp_linesContext* ReentPreParser::RegexpsContext::regexp_lines(size_t i) {
  return getRuleContext<ReentPreParser::Regexp_linesContext>(i);
}

tree::TerminalNode* ReentPreParser::RegexpsContext::Regexp_begin() {
  return getToken(ReentPreParser::Regexp_begin, 0);
}

tree::TerminalNode* ReentPreParser::RegexpsContext::Regexp_end() {
  return getToken(ReentPreParser::Regexp_end, 0);
}


size_t ReentPreParser::RegexpsContext::getRuleIndex() const {
  return ReentPreParser::RuleRegexps;
}

void ReentPreParser::RegexpsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRegexps(this);
}

void ReentPreParser::RegexpsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRegexps(this);
}

ReentPreParser::RegexpsContext* ReentPreParser::regexps() {
  RegexpsContext *_localctx = _tracker.createInstance<RegexpsContext>(_ctx, getState());
  enterRule(_localctx, 52, ReentPreParser::RuleRegexps);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(664);
    match(ReentPreParser::LeftBrace);
    setState(665);
    match(ReentPreParser::Newline);
    setState(669);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(666);
        regexp_lines(); 
      }
      setState(671);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
    }
    setState(682);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx)) {
    case 1: {
      setState(672);
      match(ReentPreParser::Regexp_begin);
      setState(673);
      match(ReentPreParser::Newline);
      setState(677);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(674);
          regexp_lines(); 
        }
        setState(679);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx);
      }
      setState(680);
      match(ReentPreParser::Regexp_end);
      setState(681);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(687);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(684);
        regexp_lines(); 
      }
      setState(689);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx);
    }
    setState(690);
    match(ReentPreParser::RightBrace);
    setState(691);
    match(ReentPreParser::Semi);
    setState(692);
    match(ReentPreParser::Newline);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Regexp_linesContext ------------------------------------------------------------------

ReentPreParser::Regexp_linesContext::Regexp_linesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Regexp_linesContext::Newline() {
  return getToken(ReentPreParser::Newline, 0);
}

ReentPreParser::Regexp_bodyContext* ReentPreParser::Regexp_linesContext::regexp_body() {
  return getRuleContext<ReentPreParser::Regexp_bodyContext>(0);
}


size_t ReentPreParser::Regexp_linesContext::getRuleIndex() const {
  return ReentPreParser::RuleRegexp_lines;
}

void ReentPreParser::Regexp_linesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRegexp_lines(this);
}

void ReentPreParser::Regexp_linesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRegexp_lines(this);
}

ReentPreParser::Regexp_linesContext* ReentPreParser::regexp_lines() {
  Regexp_linesContext *_localctx = _tracker.createInstance<Regexp_linesContext>(_ctx, getState());
  enterRule(_localctx, 54, ReentPreParser::RuleRegexp_lines);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(695);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 85, _ctx)) {
    case 1: {
      setState(694);
      regexp_body();
      break;
    }

    default:
      break;
    }
    setState(697);
    match(ReentPreParser::Newline);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Regexp_bodyContext ------------------------------------------------------------------

ReentPreParser::Regexp_bodyContext::Regexp_bodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Regexp_bodyContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_bodyContext::Regexp_set() {
  return getToken(ReentPreParser::Regexp_set, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_bodyContext::Regexp_fragment() {
  return getToken(ReentPreParser::Regexp_fragment, 0);
}

std::vector<ReentPreParser::Regexp_bodyContext *> ReentPreParser::Regexp_bodyContext::regexp_body() {
  return getRuleContexts<ReentPreParser::Regexp_bodyContext>();
}

ReentPreParser::Regexp_bodyContext* ReentPreParser::Regexp_bodyContext::regexp_body(size_t i) {
  return getRuleContext<ReentPreParser::Regexp_bodyContext>(i);
}

ReentPreParser::Plc_regexp_logicalContext* ReentPreParser::Regexp_bodyContext::plc_regexp_logical() {
  return getRuleContext<ReentPreParser::Plc_regexp_logicalContext>(0);
}

tree::TerminalNode* ReentPreParser::Regexp_bodyContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Regexp_bodyContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Regexp_bodyContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}


size_t ReentPreParser::Regexp_bodyContext::getRuleIndex() const {
  return ReentPreParser::RuleRegexp_body;
}

void ReentPreParser::Regexp_bodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRegexp_body(this);
}

void ReentPreParser::Regexp_bodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRegexp_body(this);
}

ReentPreParser::Regexp_bodyContext* ReentPreParser::regexp_body() {
  Regexp_bodyContext *_localctx = _tracker.createInstance<Regexp_bodyContext>(_ctx, getState());
  enterRule(_localctx, 56, ReentPreParser::RuleRegexp_body);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(699);

    if (!(
    		!_input->LT(-1) || _input->LT(-1)->getText()!="\n" ||
    		(_input->LT(1) && _input->LT(1)->getText() != "@begin" && _input->LT(1)->getText() != "@end" &&
    		 (_input->LT(1)->getText() != "}" || _input->LT(2) && _input->LT(2)->getText() != ";"))
    	)) throw FailedPredicateException(this, "\n\t\t!_input->LT(-1) || _input->LT(-1)->getText()!=\"\\n\" ||\n\t\t(_input->LT(1) && _input->LT(1)->getText() != \"@begin\" && _input->LT(1)->getText() != \"@end\" &&\n\t\t (_input->LT(1)->getText() != \"}\" || _input->LT(2) && _input->LT(2)->getText() != \";\"))\n\t");
    setState(714);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::LeftParen: {
        setState(700);
        match(ReentPreParser::LeftParen);
        setState(705);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(703);
            _errHandler->sync(this);
            switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 86, _ctx)) {
            case 1: {
              setState(701);
              regexp_body();
              break;
            }

            case 2: {
              setState(702);
              match(ReentPreParser::Newline);
              break;
            }

            default:
              break;
            } 
          }
          setState(707);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx);
        }
        setState(710);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case ReentPreParser::Plc_regexp_var:
          case ReentPreParser::Plc_regexp_equal:
          case ReentPreParser::Plc_regexp_not_equal:
          case ReentPreParser::Plc_regexp_query: {
            setState(708);
            plc_regexp_logical();
            break;
          }

          case ReentPreParser::RightParen: {
            setState(709);
            match(ReentPreParser::RightParen);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

      case ReentPreParser::Regexp_set: {
        setState(712);
        match(ReentPreParser::Regexp_set);
        break;
      }

      case ReentPreParser::Regexp_fragment: {
        setState(713);
        match(ReentPreParser::Regexp_fragment);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(717);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 90, _ctx)) {
    case 1: {
      setState(716);
      regexp_body();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Plc_regexp_logicalContext ------------------------------------------------------------------

ReentPreParser::Plc_regexp_logicalContext::Plc_regexp_logicalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::Plc_regexp_varContext* ReentPreParser::Plc_regexp_logicalContext::plc_regexp_var() {
  return getRuleContext<ReentPreParser::Plc_regexp_varContext>(0);
}

ReentPreParser::Plc_regexp_equalContext* ReentPreParser::Plc_regexp_logicalContext::plc_regexp_equal() {
  return getRuleContext<ReentPreParser::Plc_regexp_equalContext>(0);
}

ReentPreParser::Plc_regexp_not_equalContext* ReentPreParser::Plc_regexp_logicalContext::plc_regexp_not_equal() {
  return getRuleContext<ReentPreParser::Plc_regexp_not_equalContext>(0);
}

ReentPreParser::Plc_regexp_queryContext* ReentPreParser::Plc_regexp_logicalContext::plc_regexp_query() {
  return getRuleContext<ReentPreParser::Plc_regexp_queryContext>(0);
}


size_t ReentPreParser::Plc_regexp_logicalContext::getRuleIndex() const {
  return ReentPreParser::RulePlc_regexp_logical;
}

void ReentPreParser::Plc_regexp_logicalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlc_regexp_logical(this);
}

void ReentPreParser::Plc_regexp_logicalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlc_regexp_logical(this);
}

ReentPreParser::Plc_regexp_logicalContext* ReentPreParser::plc_regexp_logical() {
  Plc_regexp_logicalContext *_localctx = _tracker.createInstance<Plc_regexp_logicalContext>(_ctx, getState());
  enterRule(_localctx, 58, ReentPreParser::RulePlc_regexp_logical);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(723);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Plc_regexp_var: {
        enterOuterAlt(_localctx, 1);
        setState(719);
        plc_regexp_var();
        break;
      }

      case ReentPreParser::Plc_regexp_equal: {
        enterOuterAlt(_localctx, 2);
        setState(720);
        plc_regexp_equal();
        break;
      }

      case ReentPreParser::Plc_regexp_not_equal: {
        enterOuterAlt(_localctx, 3);
        setState(721);
        plc_regexp_not_equal();
        break;
      }

      case ReentPreParser::Plc_regexp_query: {
        enterOuterAlt(_localctx, 4);
        setState(722);
        plc_regexp_query();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Plc_regexp_varContext ------------------------------------------------------------------

ReentPreParser::Plc_regexp_varContext::Plc_regexp_varContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Plc_regexp_varContext::Plc_regexp_var() {
  return getToken(ReentPreParser::Plc_regexp_var, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Plc_regexp_varContext::Identifier() {
  return getTokens(ReentPreParser::Identifier);
}

tree::TerminalNode* ReentPreParser::Plc_regexp_varContext::Identifier(size_t i) {
  return getToken(ReentPreParser::Identifier, i);
}

tree::TerminalNode* ReentPreParser::Plc_regexp_varContext::Dot() {
  return getToken(ReentPreParser::Dot, 0);
}

tree::TerminalNode* ReentPreParser::Plc_regexp_varContext::LeftBrace() {
  return getToken(ReentPreParser::LeftBrace, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Plc_regexp_varContext::RightBrace() {
  return getTokens(ReentPreParser::RightBrace);
}

tree::TerminalNode* ReentPreParser::Plc_regexp_varContext::RightBrace(size_t i) {
  return getToken(ReentPreParser::RightBrace, i);
}


size_t ReentPreParser::Plc_regexp_varContext::getRuleIndex() const {
  return ReentPreParser::RulePlc_regexp_var;
}

void ReentPreParser::Plc_regexp_varContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlc_regexp_var(this);
}

void ReentPreParser::Plc_regexp_varContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlc_regexp_var(this);
}

ReentPreParser::Plc_regexp_varContext* ReentPreParser::plc_regexp_var() {
  Plc_regexp_varContext *_localctx = _tracker.createInstance<Plc_regexp_varContext>(_ctx, getState());
  enterRule(_localctx, 60, ReentPreParser::RulePlc_regexp_var);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(725);
    match(ReentPreParser::Plc_regexp_var);

    setState(726);
    dynamic_cast<Plc_regexp_varContext *>(_localctx)->lib_or_id = match(ReentPreParser::Identifier);
    setState(737);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 92, _ctx)) {
    case 1: {
      setState(727);
      match(ReentPreParser::Dot);
      setState(728);
      match(ReentPreParser::Identifier);
      setState(729);
      match(ReentPreParser::LeftBrace);
      setState(730);
      dynamic_cast<Plc_regexp_varContext *>(_localctx)->var = match(ReentPreParser::Identifier);
      setState(731);
      match(ReentPreParser::RightBrace);
      setState(732);
      match(ReentPreParser::RightBrace);
       regexp_vars.insert((dynamic_cast<Plc_regexp_varContext *>(_localctx)->var != nullptr ? dynamic_cast<Plc_regexp_varContext *>(_localctx)->var->getText() : "")); 
      break;
    }

    case 2: {
      setState(734);
      match(ReentPreParser::RightBrace);
       regexp_vars.insert((dynamic_cast<Plc_regexp_varContext *>(_localctx)->lib_or_id != nullptr ? dynamic_cast<Plc_regexp_varContext *>(_localctx)->lib_or_id->getText() : "")); 
      break;
    }

    case 3: {
       throw FailedPredicateException(this, "->{Id} expected"); 
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Plc_regexp_equalContext ------------------------------------------------------------------

ReentPreParser::Plc_regexp_equalContext::Plc_regexp_equalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Plc_regexp_equalContext::Plc_regexp_equal() {
  return getToken(ReentPreParser::Plc_regexp_equal, 0);
}

tree::TerminalNode* ReentPreParser::Plc_regexp_equalContext::RightBrace() {
  return getToken(ReentPreParser::RightBrace, 0);
}

tree::TerminalNode* ReentPreParser::Plc_regexp_equalContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}


size_t ReentPreParser::Plc_regexp_equalContext::getRuleIndex() const {
  return ReentPreParser::RulePlc_regexp_equal;
}

void ReentPreParser::Plc_regexp_equalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlc_regexp_equal(this);
}

void ReentPreParser::Plc_regexp_equalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlc_regexp_equal(this);
}

ReentPreParser::Plc_regexp_equalContext* ReentPreParser::plc_regexp_equal() {
  Plc_regexp_equalContext *_localctx = _tracker.createInstance<Plc_regexp_equalContext>(_ctx, getState());
  enterRule(_localctx, 62, ReentPreParser::RulePlc_regexp_equal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(739);
    match(ReentPreParser::Plc_regexp_equal);
    setState(742);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Identifier: {
        setState(740);
        dynamic_cast<Plc_regexp_equalContext *>(_localctx)->req = match(ReentPreParser::Identifier);
        break;
      }

      case ReentPreParser::RightBrace: {
         throw FailedPredicateException(this, "==>{Id} expected"); 
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(744);
    match(ReentPreParser::RightBrace);

    		regexp_refs.insert((dynamic_cast<Plc_regexp_equalContext *>(_localctx)->req != nullptr ? dynamic_cast<Plc_regexp_equalContext *>(_localctx)->req->getText() : ""));
    	
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Plc_regexp_not_equalContext ------------------------------------------------------------------

ReentPreParser::Plc_regexp_not_equalContext::Plc_regexp_not_equalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Plc_regexp_not_equalContext::Plc_regexp_not_equal() {
  return getToken(ReentPreParser::Plc_regexp_not_equal, 0);
}

tree::TerminalNode* ReentPreParser::Plc_regexp_not_equalContext::RightBrace() {
  return getToken(ReentPreParser::RightBrace, 0);
}

tree::TerminalNode* ReentPreParser::Plc_regexp_not_equalContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}


size_t ReentPreParser::Plc_regexp_not_equalContext::getRuleIndex() const {
  return ReentPreParser::RulePlc_regexp_not_equal;
}

void ReentPreParser::Plc_regexp_not_equalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlc_regexp_not_equal(this);
}

void ReentPreParser::Plc_regexp_not_equalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlc_regexp_not_equal(this);
}

ReentPreParser::Plc_regexp_not_equalContext* ReentPreParser::plc_regexp_not_equal() {
  Plc_regexp_not_equalContext *_localctx = _tracker.createInstance<Plc_regexp_not_equalContext>(_ctx, getState());
  enterRule(_localctx, 64, ReentPreParser::RulePlc_regexp_not_equal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(747);
    match(ReentPreParser::Plc_regexp_not_equal);
    setState(750);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Identifier: {
        setState(748);
        dynamic_cast<Plc_regexp_not_equalContext *>(_localctx)->req = match(ReentPreParser::Identifier);
        break;
      }

      case ReentPreParser::RightBrace: {
         throw FailedPredicateException(this, "!=>{Id} expected"); 
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(752);
    match(ReentPreParser::RightBrace);

    		regexp_refs.insert((dynamic_cast<Plc_regexp_not_equalContext *>(_localctx)->req != nullptr ? dynamic_cast<Plc_regexp_not_equalContext *>(_localctx)->req->getText() : ""));
    	
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Plc_regexp_queryContext ------------------------------------------------------------------

ReentPreParser::Plc_regexp_queryContext::Plc_regexp_queryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Plc_regexp_queryContext::Plc_regexp_query() {
  return getToken(ReentPreParser::Plc_regexp_query, 0);
}

tree::TerminalNode* ReentPreParser::Plc_regexp_queryContext::RightBrace() {
  return getToken(ReentPreParser::RightBrace, 0);
}

ReentPreParser::Regexp_or_sequenceContext* ReentPreParser::Plc_regexp_queryContext::regexp_or_sequence() {
  return getRuleContext<ReentPreParser::Regexp_or_sequenceContext>(0);
}


size_t ReentPreParser::Plc_regexp_queryContext::getRuleIndex() const {
  return ReentPreParser::RulePlc_regexp_query;
}

void ReentPreParser::Plc_regexp_queryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlc_regexp_query(this);
}

void ReentPreParser::Plc_regexp_queryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlc_regexp_query(this);
}

ReentPreParser::Plc_regexp_queryContext* ReentPreParser::plc_regexp_query() {
  Plc_regexp_queryContext *_localctx = _tracker.createInstance<Plc_regexp_queryContext>(_ctx, getState());
  enterRule(_localctx, 66, ReentPreParser::RulePlc_regexp_query);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(755);
    match(ReentPreParser::Plc_regexp_query);
    setState(758);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Regexp_parallel:
      case ReentPreParser::Regexp_sequential:
      case ReentPreParser::LeftParen:
      case ReentPreParser::Not:
      case ReentPreParser::Identifier:
      case ReentPreParser::Newline: {
        setState(756);
        regexp_or_sequence();
        break;
      }

      case ReentPreParser::RightBrace: {
         throw FailedPredicateException(this, "=>{op[,op]} unrecognized"); 
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(760);
    match(ReentPreParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Regexp_or_sequenceContext ------------------------------------------------------------------

ReentPreParser::Regexp_or_sequenceContext::Regexp_or_sequenceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Regexp_and_sequenceContext *> ReentPreParser::Regexp_or_sequenceContext::regexp_and_sequence() {
  return getRuleContexts<ReentPreParser::Regexp_and_sequenceContext>();
}

ReentPreParser::Regexp_and_sequenceContext* ReentPreParser::Regexp_or_sequenceContext::regexp_and_sequence(size_t i) {
  return getRuleContext<ReentPreParser::Regexp_and_sequenceContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Regexp_or_sequenceContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Regexp_or_sequenceContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Regexp_or_sequenceContext::Semi() {
  return getTokens(ReentPreParser::Semi);
}

tree::TerminalNode* ReentPreParser::Regexp_or_sequenceContext::Semi(size_t i) {
  return getToken(ReentPreParser::Semi, i);
}


size_t ReentPreParser::Regexp_or_sequenceContext::getRuleIndex() const {
  return ReentPreParser::RuleRegexp_or_sequence;
}

void ReentPreParser::Regexp_or_sequenceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRegexp_or_sequence(this);
}

void ReentPreParser::Regexp_or_sequenceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRegexp_or_sequence(this);
}

ReentPreParser::Regexp_or_sequenceContext* ReentPreParser::regexp_or_sequence() {
  Regexp_or_sequenceContext *_localctx = _tracker.createInstance<Regexp_or_sequenceContext>(_ctx, getState());
  enterRule(_localctx, 68, ReentPreParser::RuleRegexp_or_sequence);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(763);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx)) {
    case 1: {
      setState(762);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(765);
    regexp_and_sequence();
    setState(776);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 99, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(767);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(766);
          match(ReentPreParser::Newline);
        }
        setState(769);
        match(ReentPreParser::Semi);
        setState(771);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx)) {
        case 1: {
          setState(770);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(773);
        regexp_and_sequence(); 
      }
      setState(778);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 99, _ctx);
    }
    setState(780);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx)) {
    case 1: {
      setState(779);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Regexp_and_sequenceContext ------------------------------------------------------------------

ReentPreParser::Regexp_and_sequenceContext::Regexp_and_sequenceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Regexp_unaryContext *> ReentPreParser::Regexp_and_sequenceContext::regexp_unary() {
  return getRuleContexts<ReentPreParser::Regexp_unaryContext>();
}

ReentPreParser::Regexp_unaryContext* ReentPreParser::Regexp_and_sequenceContext::regexp_unary(size_t i) {
  return getRuleContext<ReentPreParser::Regexp_unaryContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Regexp_and_sequenceContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Regexp_and_sequenceContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Regexp_and_sequenceContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Regexp_and_sequenceContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::Regexp_and_sequenceContext::getRuleIndex() const {
  return ReentPreParser::RuleRegexp_and_sequence;
}

void ReentPreParser::Regexp_and_sequenceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRegexp_and_sequence(this);
}

void ReentPreParser::Regexp_and_sequenceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRegexp_and_sequence(this);
}

ReentPreParser::Regexp_and_sequenceContext* ReentPreParser::regexp_and_sequence() {
  Regexp_and_sequenceContext *_localctx = _tracker.createInstance<Regexp_and_sequenceContext>(_ctx, getState());
  enterRule(_localctx, 70, ReentPreParser::RuleRegexp_and_sequence);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(783);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 101, _ctx)) {
    case 1: {
      setState(782);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(785);
    regexp_unary();
    setState(796);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 104, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(787);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(786);
          match(ReentPreParser::Newline);
        }
        setState(789);
        match(ReentPreParser::Comma);
        setState(791);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 103, _ctx)) {
        case 1: {
          setState(790);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(793);
        regexp_unary(); 
      }
      setState(798);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 104, _ctx);
    }
    setState(800);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 105, _ctx)) {
    case 1: {
      setState(799);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Regexp_unaryContext ------------------------------------------------------------------

ReentPreParser::Regexp_unaryContext::Regexp_unaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Regexp_unaryContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

ReentPreParser::Regexp_or_sequenceContext* ReentPreParser::Regexp_unaryContext::regexp_or_sequence() {
  return getRuleContext<ReentPreParser::Regexp_or_sequenceContext>(0);
}

tree::TerminalNode* ReentPreParser::Regexp_unaryContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Regexp_unaryContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Regexp_unaryContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

ReentPreParser::Regexp_predContext* ReentPreParser::Regexp_unaryContext::regexp_pred() {
  return getRuleContext<ReentPreParser::Regexp_predContext>(0);
}


size_t ReentPreParser::Regexp_unaryContext::getRuleIndex() const {
  return ReentPreParser::RuleRegexp_unary;
}

void ReentPreParser::Regexp_unaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRegexp_unary(this);
}

void ReentPreParser::Regexp_unaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRegexp_unary(this);
}

ReentPreParser::Regexp_unaryContext* ReentPreParser::regexp_unary() {
  Regexp_unaryContext *_localctx = _tracker.createInstance<Regexp_unaryContext>(_ctx, getState());
  enterRule(_localctx, 72, ReentPreParser::RuleRegexp_unary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(824);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 112, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(803);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(802);
        match(ReentPreParser::Newline);
      }
      setState(805);
      match(ReentPreParser::LeftParen);
      setState(807);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 107, _ctx)) {
      case 1: {
        setState(806);
        match(ReentPreParser::Newline);
        break;
      }

      default:
        break;
      }
      setState(809);
      regexp_or_sequence();
      setState(811);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(810);
        match(ReentPreParser::Newline);
      }
      setState(813);
      match(ReentPreParser::RightParen);
      setState(815);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 109, _ctx)) {
      case 1: {
        setState(814);
        match(ReentPreParser::Newline);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(818);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(817);
        match(ReentPreParser::Newline);
      }
      setState(820);
      regexp_pred();
      setState(822);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 111, _ctx)) {
      case 1: {
        setState(821);
        match(ReentPreParser::Newline);
        break;
      }

      default:
        break;
      }
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Regexp_predContext ------------------------------------------------------------------

ReentPreParser::Regexp_predContext::Regexp_predContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::Regexp_pred_parallelContext* ReentPreParser::Regexp_predContext::regexp_pred_parallel() {
  return getRuleContext<ReentPreParser::Regexp_pred_parallelContext>(0);
}

tree::TerminalNode* ReentPreParser::Regexp_predContext::Regexp_sequential() {
  return getToken(ReentPreParser::Regexp_sequential, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Regexp_predContext::Identifier() {
  return getTokens(ReentPreParser::Identifier);
}

tree::TerminalNode* ReentPreParser::Regexp_predContext::Identifier(size_t i) {
  return getToken(ReentPreParser::Identifier, i);
}

tree::TerminalNode* ReentPreParser::Regexp_predContext::Not() {
  return getToken(ReentPreParser::Not, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_predContext::Dot() {
  return getToken(ReentPreParser::Dot, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_predContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_predContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

std::vector<ReentPreParser::Regexp_pred_argContext *> ReentPreParser::Regexp_predContext::regexp_pred_arg() {
  return getRuleContexts<ReentPreParser::Regexp_pred_argContext>();
}

ReentPreParser::Regexp_pred_argContext* ReentPreParser::Regexp_predContext::regexp_pred_arg(size_t i) {
  return getRuleContext<ReentPreParser::Regexp_pred_argContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Regexp_predContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Regexp_predContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Regexp_predContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Regexp_predContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::Regexp_predContext::getRuleIndex() const {
  return ReentPreParser::RuleRegexp_pred;
}

void ReentPreParser::Regexp_predContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRegexp_pred(this);
}

void ReentPreParser::Regexp_predContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRegexp_pred(this);
}

ReentPreParser::Regexp_predContext* ReentPreParser::regexp_pred() {
  Regexp_predContext *_localctx = _tracker.createInstance<Regexp_predContext>(_ctx, getState());
  enterRule(_localctx, 74, ReentPreParser::RuleRegexp_pred);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(862);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Regexp_parallel: {
        enterOuterAlt(_localctx, 1);
        setState(826);
        regexp_pred_parallel();
        break;
      }

      case ReentPreParser::Regexp_sequential: {
        enterOuterAlt(_localctx, 2);
        setState(827);
        match(ReentPreParser::Regexp_sequential);
        break;
      }

      case ReentPreParser::Not:
      case ReentPreParser::Identifier: {
        enterOuterAlt(_localctx, 3);
        setState(829);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Not) {
          setState(828);
          match(ReentPreParser::Not);
        }
        setState(831);
        match(ReentPreParser::Identifier);
        setState(834);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Dot) {
          setState(832);
          match(ReentPreParser::Dot);
          setState(833);
          match(ReentPreParser::Identifier);
        }
        setState(860);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::LeftParen) {
          setState(836);
          match(ReentPreParser::LeftParen);
          setState(854);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 119, _ctx)) {
          case 1: {
            setState(838);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == ReentPreParser::Newline) {
              setState(837);
              match(ReentPreParser::Newline);
            }
            setState(840);
            regexp_pred_arg();
            setState(851);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 118, _ctx);
            while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
              if (alt == 1) {
                setState(842);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == ReentPreParser::Newline) {
                  setState(841);
                  match(ReentPreParser::Newline);
                }
                setState(844);
                match(ReentPreParser::Comma);
                setState(846);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == ReentPreParser::Newline) {
                  setState(845);
                  match(ReentPreParser::Newline);
                }
                setState(848);
                regexp_pred_arg(); 
              }
              setState(853);
              _errHandler->sync(this);
              alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 118, _ctx);
            }
            break;
          }

          default:
            break;
          }
          setState(857);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == ReentPreParser::Newline) {
            setState(856);
            match(ReentPreParser::Newline);
          }
          setState(859);
          match(ReentPreParser::RightParen);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Regexp_pred_argContext ------------------------------------------------------------------

ReentPreParser::Regexp_pred_argContext::Regexp_pred_argContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Regexp_pred_argContext::Underscore() {
  return getToken(ReentPreParser::Underscore, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_pred_argContext::Regexp_ref() {
  return getToken(ReentPreParser::Regexp_ref, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_pred_argContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_pred_argContext::StringLiteral() {
  return getToken(ReentPreParser::StringLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_pred_argContext::CharacterLiteral() {
  return getToken(ReentPreParser::CharacterLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_pred_argContext::EmptyAtom() {
  return getToken(ReentPreParser::EmptyAtom, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_pred_argContext::IntegerLiteral() {
  return getToken(ReentPreParser::IntegerLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_pred_argContext::FloatingLiteral() {
  return getToken(ReentPreParser::FloatingLiteral, 0);
}


size_t ReentPreParser::Regexp_pred_argContext::getRuleIndex() const {
  return ReentPreParser::RuleRegexp_pred_arg;
}

void ReentPreParser::Regexp_pred_argContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRegexp_pred_arg(this);
}

void ReentPreParser::Regexp_pred_argContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRegexp_pred_arg(this);
}

ReentPreParser::Regexp_pred_argContext* ReentPreParser::regexp_pred_arg() {
  Regexp_pred_argContext *_localctx = _tracker.createInstance<Regexp_pred_argContext>(_ctx, getState());
  enterRule(_localctx, 76, ReentPreParser::RuleRegexp_pred_arg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(877);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Underscore: {
        enterOuterAlt(_localctx, 1);
        setState(864);
        match(ReentPreParser::Underscore);
        break;
      }

      case ReentPreParser::Regexp_ref: {
        enterOuterAlt(_localctx, 2);
        setState(865);
        match(ReentPreParser::Regexp_ref);
        setState(868);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Identifier) {
          setState(866);
          dynamic_cast<Regexp_pred_argContext *>(_localctx)->ref = match(ReentPreParser::Identifier);
           regexp_refs.insert((dynamic_cast<Regexp_pred_argContext *>(_localctx)->ref != nullptr ? dynamic_cast<Regexp_pred_argContext *>(_localctx)->ref->getText() : "")); 
        }
        break;
      }

      case ReentPreParser::StringLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(870);
        match(ReentPreParser::StringLiteral);
        break;
      }

      case ReentPreParser::CharacterLiteral: {
        enterOuterAlt(_localctx, 4);
        setState(871);
        match(ReentPreParser::CharacterLiteral);
        break;
      }

      case ReentPreParser::EmptyAtom: {
        enterOuterAlt(_localctx, 5);
        setState(872);
        match(ReentPreParser::EmptyAtom);
        break;
      }

      case ReentPreParser::IntegerLiteral: {
        enterOuterAlt(_localctx, 6);
        setState(873);
        match(ReentPreParser::IntegerLiteral);
        break;
      }

      case ReentPreParser::FloatingLiteral: {
        enterOuterAlt(_localctx, 7);
        setState(874);
        match(ReentPreParser::FloatingLiteral);
        break;
      }

      case ReentPreParser::Identifier: {
        enterOuterAlt(_localctx, 8);
        setState(875);
        dynamic_cast<Regexp_pred_argContext *>(_localctx)->var = match(ReentPreParser::Identifier);
         regexp_refs.insert((dynamic_cast<Regexp_pred_argContext *>(_localctx)->var != nullptr ? dynamic_cast<Regexp_pred_argContext *>(_localctx)->var->getText() : "")); 
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Regexp_pred_parallelContext ------------------------------------------------------------------

ReentPreParser::Regexp_pred_parallelContext::Regexp_pred_parallelContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Regexp_pred_parallelContext::Regexp_parallel() {
  return getToken(ReentPreParser::Regexp_parallel, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Regexp_pred_parallelContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Regexp_pred_parallelContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

tree::TerminalNode* ReentPreParser::Regexp_pred_parallelContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_pred_parallelContext::Regexp_analyze() {
  return getToken(ReentPreParser::Regexp_analyze, 0);
}

tree::TerminalNode* ReentPreParser::Regexp_pred_parallelContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}


size_t ReentPreParser::Regexp_pred_parallelContext::getRuleIndex() const {
  return ReentPreParser::RuleRegexp_pred_parallel;
}

void ReentPreParser::Regexp_pred_parallelContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRegexp_pred_parallel(this);
}

void ReentPreParser::Regexp_pred_parallelContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRegexp_pred_parallel(this);
}

ReentPreParser::Regexp_pred_parallelContext* ReentPreParser::regexp_pred_parallel() {
  Regexp_pred_parallelContext *_localctx = _tracker.createInstance<Regexp_pred_parallelContext>(_ctx, getState());
  enterRule(_localctx, 78, ReentPreParser::RuleRegexp_pred_parallel);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(879);
    match(ReentPreParser::Regexp_parallel);
    setState(881);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 125, _ctx)) {
    case 1: {
      setState(880);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(892);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftParen) {
      setState(883);
      match(ReentPreParser::LeftParen);
      setState(885);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(884);
        match(ReentPreParser::Newline);
      }
      setState(887);
      match(ReentPreParser::Regexp_analyze);
      setState(889);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(888);
        match(ReentPreParser::Newline);
      }
      setState(891);
      match(ReentPreParser::RightParen);
    }
    setState(895);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 129, _ctx)) {
    case 1: {
      setState(894);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefModuleContext ------------------------------------------------------------------

ReentPreParser::DefModuleContext::DefModuleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::DefModuleContext::DefModule() {
  return getToken(ReentPreParser::DefModule, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::DefModuleContext::LeftParen() {
  return getTokens(ReentPreParser::LeftParen);
}

tree::TerminalNode* ReentPreParser::DefModuleContext::LeftParen(size_t i) {
  return getToken(ReentPreParser::LeftParen, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::DefModuleContext::RightParen() {
  return getTokens(ReentPreParser::RightParen);
}

tree::TerminalNode* ReentPreParser::DefModuleContext::RightParen(size_t i) {
  return getToken(ReentPreParser::RightParen, i);
}

tree::TerminalNode* ReentPreParser::DefModuleContext::LeftBrace() {
  return getToken(ReentPreParser::LeftBrace, 0);
}

ReentPreParser::DefModuleDescriptorsContext* ReentPreParser::DefModuleContext::defModuleDescriptors() {
  return getRuleContext<ReentPreParser::DefModuleDescriptorsContext>(0);
}

std::vector<tree::TerminalNode *> ReentPreParser::DefModuleContext::Identifier() {
  return getTokens(ReentPreParser::Identifier);
}

tree::TerminalNode* ReentPreParser::DefModuleContext::Identifier(size_t i) {
  return getToken(ReentPreParser::Identifier, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::DefModuleContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::DefModuleContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::DefModuleContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::DefModuleContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::DefModuleContext::getRuleIndex() const {
  return ReentPreParser::RuleDefModule;
}

void ReentPreParser::DefModuleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefModule(this);
}

void ReentPreParser::DefModuleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefModule(this);
}

ReentPreParser::DefModuleContext* ReentPreParser::defModule() {
  DefModuleContext *_localctx = _tracker.createInstance<DefModuleContext>(_ctx, getState());
  enterRule(_localctx, 80, ReentPreParser::RuleDefModule);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(897);
    match(ReentPreParser::DefModule);
    setState(898);
    match(ReentPreParser::LeftParen);
    setState(900);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Identifier) {
      setState(899);
      match(ReentPreParser::Identifier);
    }
    setState(902);
    match(ReentPreParser::RightParen);
    setState(903);
    dynamic_cast<DefModuleContext *>(_localctx)->ident = match(ReentPreParser::Identifier);
    setState(904);
    match(ReentPreParser::LeftParen);
     int param_counter = 0; 
    setState(916);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Identifier) {
      setState(906);
      match(ReentPreParser::Identifier);
       param_counter++; 
      setState(913);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Comma) {
        setState(908);
        match(ReentPreParser::Comma);
        setState(909);
        match(ReentPreParser::Identifier);
         param_counter++; 
        setState(915);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(918);
    match(ReentPreParser::RightParen);

    		modules[(dynamic_cast<DefModuleContext *>(_localctx)->ident != nullptr ? dynamic_cast<DefModuleContext *>(_localctx)->ident->getText() : "")] = param_counter;
    	
    setState(923);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(920);
      match(ReentPreParser::Newline);
      setState(925);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(926);
    match(ReentPreParser::LeftBrace);
    setState(930);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 134, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(927);
        match(ReentPreParser::Newline); 
      }
      setState(932);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 134, _ctx);
    }
    setState(933);
    defModuleDescriptors();
    setState(937);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 135, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(934);
        match(ReentPreParser::Newline); 
      }
      setState(939);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 135, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefModuleDescriptorsContext ------------------------------------------------------------------

ReentPreParser::DefModuleDescriptorsContext::DefModuleDescriptorsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::DefModuleDescriptorContext* ReentPreParser::DefModuleDescriptorsContext::defModuleDescriptor() {
  return getRuleContext<ReentPreParser::DefModuleDescriptorContext>(0);
}

tree::TerminalNode* ReentPreParser::DefModuleDescriptorsContext::RightBrace() {
  return getToken(ReentPreParser::RightBrace, 0);
}

tree::TerminalNode* ReentPreParser::DefModuleDescriptorsContext::Semi() {
  return getToken(ReentPreParser::Semi, 0);
}

ReentPreParser::DefModuleDescriptorsContext* ReentPreParser::DefModuleDescriptorsContext::defModuleDescriptors() {
  return getRuleContext<ReentPreParser::DefModuleDescriptorsContext>(0);
}


size_t ReentPreParser::DefModuleDescriptorsContext::getRuleIndex() const {
  return ReentPreParser::RuleDefModuleDescriptors;
}

void ReentPreParser::DefModuleDescriptorsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefModuleDescriptors(this);
}

void ReentPreParser::DefModuleDescriptorsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefModuleDescriptors(this);
}

ReentPreParser::DefModuleDescriptorsContext* ReentPreParser::defModuleDescriptors() {
  DefModuleDescriptorsContext *_localctx = _tracker.createInstance<DefModuleDescriptorsContext>(_ctx, getState());
  enterRule(_localctx, 82, ReentPreParser::RuleDefModuleDescriptors);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(940);
    defModuleDescriptor();
    setState(947);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 137, _ctx)) {
    case 1: {
      setState(941);
      match(ReentPreParser::RightBrace);
      setState(942);
      match(ReentPreParser::Semi);
      break;
    }

    case 2: {
      setState(944);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::RightBrace) {
        setState(943);
        match(ReentPreParser::RightBrace);
      }
      setState(946);
      defModuleDescriptors();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefModuleDescriptorContext ------------------------------------------------------------------

ReentPreParser::DefModuleDescriptorContext::DefModuleDescriptorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::DefModuleDescriptorContext::At() {
  return getToken(ReentPreParser::At, 0);
}

ReentPreParser::Prolog_goalContext* ReentPreParser::DefModuleDescriptorContext::prolog_goal() {
  return getRuleContext<ReentPreParser::Prolog_goalContext>(0);
}

ReentPreParser::Prolog_statementContext* ReentPreParser::DefModuleDescriptorContext::prolog_statement() {
  return getRuleContext<ReentPreParser::Prolog_statementContext>(0);
}

ReentPreParser::Cpp_code_without_atContext* ReentPreParser::DefModuleDescriptorContext::cpp_code_without_at() {
  return getRuleContext<ReentPreParser::Cpp_code_without_atContext>(0);
}


size_t ReentPreParser::DefModuleDescriptorContext::getRuleIndex() const {
  return ReentPreParser::RuleDefModuleDescriptor;
}

void ReentPreParser::DefModuleDescriptorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefModuleDescriptor(this);
}

void ReentPreParser::DefModuleDescriptorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefModuleDescriptor(this);
}

ReentPreParser::DefModuleDescriptorContext* ReentPreParser::defModuleDescriptor() {
  DefModuleDescriptorContext *_localctx = _tracker.createInstance<DefModuleDescriptorContext>(_ctx, getState());
  enterRule(_localctx, 84, ReentPreParser::RuleDefModuleDescriptor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(956);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::At: {
        enterOuterAlt(_localctx, 1);
        setState(949);
        match(ReentPreParser::At);
        setState(953);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 138, _ctx)) {
        case 1: {
          setState(950);
          prolog_goal();
          break;
        }

        case 2: {
          setState(951);
          prolog_statement();
          break;
        }

        case 3: {
           throw FailedPredicateException(this, "Corrupted Prolog statement in module definition"); 
          break;
        }

        default:
          break;
        }
        break;
      }

      case ReentPreParser::Regexp_fragment:
      case ReentPreParser::Regexp_set:
      case ReentPreParser::IntegerLiteral:
      case ReentPreParser::CharacterLiteral:
      case ReentPreParser::FloatingLiteral:
      case ReentPreParser::StringLiteral:
      case ReentPreParser::EmptyAtom:
      case ReentPreParser::BooleanLiteral:
      case ReentPreParser::PointerLiteral:
      case ReentPreParser::UserDefinedLiteral:
      case ReentPreParser::DefModule:
      case ReentPreParser::DefMemoization:
      case ReentPreParser::DoNotCheck:
      case ReentPreParser::DefOtherPragma:
      case ReentPreParser::Introduce:
      case ReentPreParser::MetaSentence:
      case ReentPreParser::Stop:
      case ReentPreParser::PreprocPasses:
      case ReentPreParser::AddScan:
      case ReentPreParser::Scan:
      case ReentPreParser::AddParse:
      case ReentPreParser::Parse:
      case ReentPreParser::DefPattern:
      case ReentPreParser::DefXPath:
      case ReentPreParser::Line:
      case ReentPreParser::MultiLineMacro:
      case ReentPreParser::Directive:
      case ReentPreParser::AtValue:
      case ReentPreParser::Cilk_spawn:
      case ReentPreParser::Cilk_sync:
      case ReentPreParser::Conditions:
      case ReentPreParser::Controlled:
      case ReentPreParser::Div_:
      case ReentPreParser::False_:
      case ReentPreParser::Feed_forward:
      case ReentPreParser::GetText:
      case ReentPreParser::Goal:
      case ReentPreParser::Lin_extrapolator:
      case ReentPreParser::Mgua:
      case ReentPreParser::Mod_:
      case ReentPreParser::Nullptr:
      case ReentPreParser::Regexp_analyze:
      case ReentPreParser::Regexp_begin:
      case ReentPreParser::Regexp_end:
      case ReentPreParser::Regexp_parallel:
      case ReentPreParser::Regexp_sequential:
      case ReentPreParser::Rem:
      case ReentPreParser::True_:
      case ReentPreParser::Plc_regexp_var:
      case ReentPreParser::Plc_regexp_equal:
      case ReentPreParser::Plc_regexp_not_equal:
      case ReentPreParser::Plc_regexp_query:
      case ReentPreParser::LeftParen:
      case ReentPreParser::RightParen:
      case ReentPreParser::LeftBracket:
      case ReentPreParser::RightBracket:
      case ReentPreParser::LeftBrace:
      case ReentPreParser::AssignGreater:
      case ReentPreParser::DivDiv:
      case ReentPreParser::Pound:
      case ReentPreParser::And_:
      case ReentPreParser::Or_:
      case ReentPreParser::Is:
      case ReentPreParser::Is_:
      case ReentPreParser::Prolog_not:
      case ReentPreParser::Prolog_not_equal:
      case ReentPreParser::Slash:
      case ReentPreParser::ConstructAtom:
      case ReentPreParser::Regexp_ref:
      case ReentPreParser::Underscore:
      case ReentPreParser::Plus:
      case ReentPreParser::Minus:
      case ReentPreParser::Star:
      case ReentPreParser::Div:
      case ReentPreParser::Mod:
      case ReentPreParser::Caret:
      case ReentPreParser::And:
      case ReentPreParser::Or:
      case ReentPreParser::Tilde:
      case ReentPreParser::Not:
      case ReentPreParser::Assign:
      case ReentPreParser::Less:
      case ReentPreParser::Greater:
      case ReentPreParser::Equal:
      case ReentPreParser::NotEqual:
      case ReentPreParser::LessEqual:
      case ReentPreParser::GreaterEqual:
      case ReentPreParser::AndAnd:
      case ReentPreParser::OrOr:
      case ReentPreParser::Comma:
      case ReentPreParser::Arrow:
      case ReentPreParser::Question:
      case ReentPreParser::Colon:
      case ReentPreParser::Doublecolon:
      case ReentPreParser::Semi:
      case ReentPreParser::Dot:
      case ReentPreParser::DotStar:
      case ReentPreParser::Ellipsis:
      case ReentPreParser::Identifier:
      case ReentPreParser::DecimalLiteral:
      case ReentPreParser::OctalLiteral:
      case ReentPreParser::HexadecimalLiteral:
      case ReentPreParser::BinaryLiteral:
      case ReentPreParser::Integersuffix:
      case ReentPreParser::UserDefinedIntegerLiteral:
      case ReentPreParser::UserDefinedFloatingLiteral:
      case ReentPreParser::UserDefinedStringLiteral:
      case ReentPreParser::UserDefinedCharacterLiteral:
      case ReentPreParser::Whitespace:
      case ReentPreParser::Newline:
      case ReentPreParser::BlockComment:
      case ReentPreParser::LineComment:
      case ReentPreParser::PrologComment: {
        enterOuterAlt(_localctx, 2);
        setState(955);
        cpp_code_without_at();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefMemoizationContext ------------------------------------------------------------------

ReentPreParser::DefMemoizationContext::DefMemoizationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::DefMemoizationContext::DefMemoization() {
  return getToken(ReentPreParser::DefMemoization, 0);
}

tree::TerminalNode* ReentPreParser::DefMemoizationContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::DefMemoizationContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

ReentPreParser::BlockHeaderContext* ReentPreParser::DefMemoizationContext::blockHeader() {
  return getRuleContext<ReentPreParser::BlockHeaderContext>(0);
}

std::vector<ReentPreParser::MemoMapItemContext *> ReentPreParser::DefMemoizationContext::memoMapItem() {
  return getRuleContexts<ReentPreParser::MemoMapItemContext>();
}

ReentPreParser::MemoMapItemContext* ReentPreParser::DefMemoizationContext::memoMapItem(size_t i) {
  return getRuleContext<ReentPreParser::MemoMapItemContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::DefMemoizationContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::DefMemoizationContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}

ReentPreParser::MemoizationStyleContext* ReentPreParser::DefMemoizationContext::memoizationStyle() {
  return getRuleContext<ReentPreParser::MemoizationStyleContext>(0);
}

std::vector<tree::TerminalNode *> ReentPreParser::DefMemoizationContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::DefMemoizationContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}


size_t ReentPreParser::DefMemoizationContext::getRuleIndex() const {
  return ReentPreParser::RuleDefMemoization;
}

void ReentPreParser::DefMemoizationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefMemoization(this);
}

void ReentPreParser::DefMemoizationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefMemoization(this);
}

ReentPreParser::DefMemoizationContext* ReentPreParser::defMemoization() {
  DefMemoizationContext *_localctx = _tracker.createInstance<DefMemoizationContext>(_ctx, getState());
  enterRule(_localctx, 86, ReentPreParser::RuleDefMemoization);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(958);
    match(ReentPreParser::DefMemoization);
    setState(959);
    match(ReentPreParser::LeftParen);
     memo_map.clear(); int param_counter = 0; 
    setState(961);
    dynamic_cast<DefMemoizationContext *>(_localctx)->first = memoMapItem();
     param_counter++; memo_map.push_back((dynamic_cast<DefMemoizationContext *>(_localctx)->first != nullptr ? _input->getText(dynamic_cast<DefMemoizationContext *>(_localctx)->first->start, dynamic_cast<DefMemoizationContext *>(_localctx)->first->stop) : nullptr)); 
    setState(969);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(963);
      match(ReentPreParser::Comma);
      setState(964);
      dynamic_cast<DefMemoizationContext *>(_localctx)->next = memoMapItem();
       param_counter++;
      		if ((dynamic_cast<DefMemoizationContext *>(_localctx)->next != nullptr ? _input->getText(dynamic_cast<DefMemoizationContext *>(_localctx)->next->start, dynamic_cast<DefMemoizationContext *>(_localctx)->next->stop) : nullptr) == "*g" || (dynamic_cast<DefMemoizationContext *>(_localctx)->next != nullptr ? _input->getText(dynamic_cast<DefMemoizationContext *>(_localctx)->next->start, dynamic_cast<DefMemoizationContext *>(_localctx)->next->stop) : nullptr) == "g")
      			if (std::find(memo_map.begin(), memo_map.end(), "g") != memo_map.end() ||
      				std::find(memo_map.begin(), memo_map.end(), "*g") != memo_map.end())
      				throw FailedPredicateException(this, "only one parameter can be of type 'g'");
      		if ((dynamic_cast<DefMemoizationContext *>(_localctx)->next != nullptr ? _input->getText(dynamic_cast<DefMemoizationContext *>(_localctx)->next->start, dynamic_cast<DefMemoizationContext *>(_localctx)->next->stop) : nullptr) == "*o" || (dynamic_cast<DefMemoizationContext *>(_localctx)->next != nullptr ? _input->getText(dynamic_cast<DefMemoizationContext *>(_localctx)->next->start, dynamic_cast<DefMemoizationContext *>(_localctx)->next->stop) : nullptr) == "o")
      			if (std::find(memo_map.begin(), memo_map.end(), "o") != memo_map.end() ||
      				std::find(memo_map.begin(), memo_map.end(), "*o") != memo_map.end())
      				throw FailedPredicateException(this, "only one parameter can be of type 'o'");
      		if ((dynamic_cast<DefMemoizationContext *>(_localctx)->next != nullptr ? _input->getText(dynamic_cast<DefMemoizationContext *>(_localctx)->next->start, dynamic_cast<DefMemoizationContext *>(_localctx)->next->stop) : nullptr) == "*t" || (dynamic_cast<DefMemoizationContext *>(_localctx)->next != nullptr ? _input->getText(dynamic_cast<DefMemoizationContext *>(_localctx)->next->start, dynamic_cast<DefMemoizationContext *>(_localctx)->next->stop) : nullptr) == "t")
      			throw FailedPredicateException(this, "only first parameter can be of type 't'");
      		memo_map.push_back((dynamic_cast<DefMemoizationContext *>(_localctx)->next != nullptr ? _input->getText(dynamic_cast<DefMemoizationContext *>(_localctx)->next->start, dynamic_cast<DefMemoizationContext *>(_localctx)->next->stop) : nullptr));
      	
      setState(971);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(972);
    match(ReentPreParser::RightParen);
    setState(974);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ReentPreParser::Feed_forward)
      | (1ULL << ReentPreParser::Lin_extrapolator)
      | (1ULL << ReentPreParser::Mgua))) != 0)) {
      setState(973);
      memoizationStyle();
    }
    setState(977); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(976);
      match(ReentPreParser::Newline);
      setState(979); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ReentPreParser::Newline);
    setState(981);
    blockHeader();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PreprocPassesContext ------------------------------------------------------------------

ReentPreParser::PreprocPassesContext::PreprocPassesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::PreprocPassesContext::PreprocPasses() {
  return getToken(ReentPreParser::PreprocPasses, 0);
}

tree::TerminalNode* ReentPreParser::PreprocPassesContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::PreprocPassesContext::IntegerLiteral() {
  return getToken(ReentPreParser::IntegerLiteral, 0);
}

tree::TerminalNode* ReentPreParser::PreprocPassesContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

tree::TerminalNode* ReentPreParser::PreprocPassesContext::Newline() {
  return getToken(ReentPreParser::Newline, 0);
}

tree::TerminalNode* ReentPreParser::PreprocPassesContext::Comma() {
  return getToken(ReentPreParser::Comma, 0);
}

tree::TerminalNode* ReentPreParser::PreprocPassesContext::StringLiteral() {
  return getToken(ReentPreParser::StringLiteral, 0);
}


size_t ReentPreParser::PreprocPassesContext::getRuleIndex() const {
  return ReentPreParser::RulePreprocPasses;
}

void ReentPreParser::PreprocPassesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPreprocPasses(this);
}

void ReentPreParser::PreprocPassesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPreprocPasses(this);
}

ReentPreParser::PreprocPassesContext* ReentPreParser::preprocPasses() {
  PreprocPassesContext *_localctx = _tracker.createInstance<PreprocPassesContext>(_ctx, getState());
  enterRule(_localctx, 88, ReentPreParser::RulePreprocPasses);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(983);
    match(ReentPreParser::PreprocPasses);
    setState(984);
    match(ReentPreParser::LeftParen);
    setState(985);
    match(ReentPreParser::IntegerLiteral);
    setState(988);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Comma) {
      setState(986);
      match(ReentPreParser::Comma);
      setState(987);
      match(ReentPreParser::StringLiteral);
    }
    setState(990);
    match(ReentPreParser::RightParen);
    setState(991);
    match(ReentPreParser::Newline);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddScanContext ------------------------------------------------------------------

ReentPreParser::AddScanContext::AddScanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::AddScanContext::AddScan() {
  return getToken(ReentPreParser::AddScan, 0);
}

ReentPreParser::Scanners_listContext* ReentPreParser::AddScanContext::scanners_list() {
  return getRuleContext<ReentPreParser::Scanners_listContext>(0);
}

tree::TerminalNode* ReentPreParser::AddScanContext::Newline() {
  return getToken(ReentPreParser::Newline, 0);
}


size_t ReentPreParser::AddScanContext::getRuleIndex() const {
  return ReentPreParser::RuleAddScan;
}

void ReentPreParser::AddScanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddScan(this);
}

void ReentPreParser::AddScanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddScan(this);
}

ReentPreParser::AddScanContext* ReentPreParser::addScan() {
  AddScanContext *_localctx = _tracker.createInstance<AddScanContext>(_ctx, getState());
  enterRule(_localctx, 90, ReentPreParser::RuleAddScan);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(993);
    match(ReentPreParser::AddScan);
    setState(994);
    scanners_list();
    setState(995);
    match(ReentPreParser::Newline);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScanContext ------------------------------------------------------------------

ReentPreParser::ScanContext::ScanContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::ScanContext::Scan() {
  return getToken(ReentPreParser::Scan, 0);
}

ReentPreParser::Scanners_listContext* ReentPreParser::ScanContext::scanners_list() {
  return getRuleContext<ReentPreParser::Scanners_listContext>(0);
}

tree::TerminalNode* ReentPreParser::ScanContext::Newline() {
  return getToken(ReentPreParser::Newline, 0);
}


size_t ReentPreParser::ScanContext::getRuleIndex() const {
  return ReentPreParser::RuleScan;
}

void ReentPreParser::ScanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScan(this);
}

void ReentPreParser::ScanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScan(this);
}

ReentPreParser::ScanContext* ReentPreParser::scan() {
  ScanContext *_localctx = _tracker.createInstance<ScanContext>(_ctx, getState());
  enterRule(_localctx, 92, ReentPreParser::RuleScan);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(997);
    match(ReentPreParser::Scan);
    setState(998);
    scanners_list();
    setState(999);
    match(ReentPreParser::Newline);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddParseContext ------------------------------------------------------------------

ReentPreParser::AddParseContext::AddParseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::AddParseContext::AddParse() {
  return getToken(ReentPreParser::AddParse, 0);
}

ReentPreParser::Scanners_listContext* ReentPreParser::AddParseContext::scanners_list() {
  return getRuleContext<ReentPreParser::Scanners_listContext>(0);
}

tree::TerminalNode* ReentPreParser::AddParseContext::Newline() {
  return getToken(ReentPreParser::Newline, 0);
}


size_t ReentPreParser::AddParseContext::getRuleIndex() const {
  return ReentPreParser::RuleAddParse;
}

void ReentPreParser::AddParseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddParse(this);
}

void ReentPreParser::AddParseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddParse(this);
}

ReentPreParser::AddParseContext* ReentPreParser::addParse() {
  AddParseContext *_localctx = _tracker.createInstance<AddParseContext>(_ctx, getState());
  enterRule(_localctx, 94, ReentPreParser::RuleAddParse);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1001);
    match(ReentPreParser::AddParse);
    setState(1002);
    scanners_list();
    setState(1003);
    match(ReentPreParser::Newline);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParseContext ------------------------------------------------------------------

ReentPreParser::ParseContext::ParseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::ParseContext::Parse() {
  return getToken(ReentPreParser::Parse, 0);
}

ReentPreParser::Scanners_listContext* ReentPreParser::ParseContext::scanners_list() {
  return getRuleContext<ReentPreParser::Scanners_listContext>(0);
}

tree::TerminalNode* ReentPreParser::ParseContext::Newline() {
  return getToken(ReentPreParser::Newline, 0);
}


size_t ReentPreParser::ParseContext::getRuleIndex() const {
  return ReentPreParser::RuleParse;
}

void ReentPreParser::ParseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParse(this);
}

void ReentPreParser::ParseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParse(this);
}

ReentPreParser::ParseContext* ReentPreParser::parse() {
  ParseContext *_localctx = _tracker.createInstance<ParseContext>(_ctx, getState());
  enterRule(_localctx, 96, ReentPreParser::RuleParse);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1005);
    match(ReentPreParser::Parse);
    setState(1006);
    scanners_list();
    setState(1007);
    match(ReentPreParser::Newline);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Scanners_listContext ------------------------------------------------------------------

ReentPreParser::Scanners_listContext::Scanners_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Scanners_listContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::Scanners_listContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Scanners_listContext::Identifier() {
  return getTokens(ReentPreParser::Identifier);
}

tree::TerminalNode* ReentPreParser::Scanners_listContext::Identifier(size_t i) {
  return getToken(ReentPreParser::Identifier, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Scanners_listContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Scanners_listContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::Scanners_listContext::getRuleIndex() const {
  return ReentPreParser::RuleScanners_list;
}

void ReentPreParser::Scanners_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScanners_list(this);
}

void ReentPreParser::Scanners_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScanners_list(this);
}

ReentPreParser::Scanners_listContext* ReentPreParser::scanners_list() {
  Scanners_listContext *_localctx = _tracker.createInstance<Scanners_listContext>(_ctx, getState());
  enterRule(_localctx, 98, ReentPreParser::RuleScanners_list);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1009);
    match(ReentPreParser::LeftParen);
    setState(1010);
    dynamic_cast<Scanners_listContext *>(_localctx)->first = match(ReentPreParser::Identifier);

    			scanner_refs.insert((dynamic_cast<Scanners_listContext *>(_localctx)->first != nullptr ? dynamic_cast<Scanners_listContext *>(_localctx)->first->getText() : ""));
    		
    setState(1017);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(1012);
      match(ReentPreParser::Comma);
      setState(1013);
      dynamic_cast<Scanners_listContext *>(_localctx)->next = match(ReentPreParser::Identifier);

      			scanner_refs.insert((dynamic_cast<Scanners_listContext *>(_localctx)->next != nullptr ? dynamic_cast<Scanners_listContext *>(_localctx)->next->getText() : ""));
      		
      setState(1019);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1020);
    match(ReentPreParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MemoMapItemContext ------------------------------------------------------------------

ReentPreParser::MemoMapItemContext::MemoMapItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::MemoMapTypeContext* ReentPreParser::MemoMapItemContext::memoMapType() {
  return getRuleContext<ReentPreParser::MemoMapTypeContext>(0);
}

tree::TerminalNode* ReentPreParser::MemoMapItemContext::Star() {
  return getToken(ReentPreParser::Star, 0);
}


size_t ReentPreParser::MemoMapItemContext::getRuleIndex() const {
  return ReentPreParser::RuleMemoMapItem;
}

void ReentPreParser::MemoMapItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMemoMapItem(this);
}

void ReentPreParser::MemoMapItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMemoMapItem(this);
}

ReentPreParser::MemoMapItemContext* ReentPreParser::memoMapItem() {
  MemoMapItemContext *_localctx = _tracker.createInstance<MemoMapItemContext>(_ctx, getState());
  enterRule(_localctx, 100, ReentPreParser::RuleMemoMapItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1023);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 145, _ctx)) {
    case 1: {
      setState(1022);
      match(ReentPreParser::Star);
      break;
    }

    default:
      break;
    }
    setState(1025);
    memoMapType();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MemoMapTypeContext ------------------------------------------------------------------

ReentPreParser::MemoMapTypeContext::MemoMapTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::MemoMapTypeContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}


size_t ReentPreParser::MemoMapTypeContext::getRuleIndex() const {
  return ReentPreParser::RuleMemoMapType;
}

void ReentPreParser::MemoMapTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMemoMapType(this);
}

void ReentPreParser::MemoMapTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMemoMapType(this);
}

ReentPreParser::MemoMapTypeContext* ReentPreParser::memoMapType() {
  MemoMapTypeContext *_localctx = _tracker.createInstance<MemoMapTypeContext>(_ctx, getState());
  enterRule(_localctx, 102, ReentPreParser::RuleMemoMapType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1030);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 146, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1027);

      if (!( _input->LT(1)->getText() == "i" || _input->LT(1)->getText() == "o" ||
      	  _input->LT(1)->getText() == "g" || _input->LT(1)->getText() == "t" )) throw FailedPredicateException(this, " _input->LT(1)->getText() == \"i\" || _input->LT(1)->getText() == \"o\" ||\n\t  _input->LT(1)->getText() == \"g\" || _input->LT(1)->getText() == \"t\" ");
      setState(1028);
      match(ReentPreParser::Identifier);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
       throw FailedPredicateException(this,
      		std::string("Wrong map descriptor '")+
      		_input->LT(1)->getText()+
      		std::string("'. Must be one of ['i','o','g','t']")); 
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Cpp_balanced_expressionContext ------------------------------------------------------------------

ReentPreParser::Cpp_balanced_expressionContext::Cpp_balanced_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ReentPreParser::Cpp_balanced_expressionContext::Identifier() {
  return getTokens(ReentPreParser::Identifier);
}

tree::TerminalNode* ReentPreParser::Cpp_balanced_expressionContext::Identifier(size_t i) {
  return getToken(ReentPreParser::Identifier, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Cpp_balanced_expressionContext::LeftParen() {
  return getTokens(ReentPreParser::LeftParen);
}

tree::TerminalNode* ReentPreParser::Cpp_balanced_expressionContext::LeftParen(size_t i) {
  return getToken(ReentPreParser::LeftParen, i);
}

std::vector<ReentPreParser::Cpp_balanced_expressionContext *> ReentPreParser::Cpp_balanced_expressionContext::cpp_balanced_expression() {
  return getRuleContexts<ReentPreParser::Cpp_balanced_expressionContext>();
}

ReentPreParser::Cpp_balanced_expressionContext* ReentPreParser::Cpp_balanced_expressionContext::cpp_balanced_expression(size_t i) {
  return getRuleContext<ReentPreParser::Cpp_balanced_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Cpp_balanced_expressionContext::RightParen() {
  return getTokens(ReentPreParser::RightParen);
}

tree::TerminalNode* ReentPreParser::Cpp_balanced_expressionContext::RightParen(size_t i) {
  return getToken(ReentPreParser::RightParen, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Cpp_balanced_expressionContext::LeftBracket() {
  return getTokens(ReentPreParser::LeftBracket);
}

tree::TerminalNode* ReentPreParser::Cpp_balanced_expressionContext::LeftBracket(size_t i) {
  return getToken(ReentPreParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Cpp_balanced_expressionContext::RightBracket() {
  return getTokens(ReentPreParser::RightBracket);
}

tree::TerminalNode* ReentPreParser::Cpp_balanced_expressionContext::RightBracket(size_t i) {
  return getToken(ReentPreParser::RightBracket, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Cpp_balanced_expressionContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Cpp_balanced_expressionContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::Cpp_balanced_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleCpp_balanced_expression;
}

void ReentPreParser::Cpp_balanced_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCpp_balanced_expression(this);
}

void ReentPreParser::Cpp_balanced_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCpp_balanced_expression(this);
}

ReentPreParser::Cpp_balanced_expressionContext* ReentPreParser::cpp_balanced_expression() {
  Cpp_balanced_expressionContext *_localctx = _tracker.createInstance<Cpp_balanced_expressionContext>(_ctx, getState());
  enterRule(_localctx, 104, ReentPreParser::RuleCpp_balanced_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1060);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Identifier: {
        setState(1032);
        match(ReentPreParser::Identifier);
        setState(1045);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 149, _ctx)) {
        case 1: {
          setState(1033);
          match(ReentPreParser::LeftParen);
          setState(1042);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << ReentPreParser::Regexp_fragment)
            | (1ULL << ReentPreParser::Regexp_set)
            | (1ULL << ReentPreParser::IntegerLiteral)
            | (1ULL << ReentPreParser::CharacterLiteral)
            | (1ULL << ReentPreParser::FloatingLiteral)
            | (1ULL << ReentPreParser::StringLiteral)
            | (1ULL << ReentPreParser::EmptyAtom)
            | (1ULL << ReentPreParser::BooleanLiteral)
            | (1ULL << ReentPreParser::PointerLiteral)
            | (1ULL << ReentPreParser::UserDefinedLiteral)
            | (1ULL << ReentPreParser::DefModule)
            | (1ULL << ReentPreParser::DefMemoization)
            | (1ULL << ReentPreParser::DoNotCheck)
            | (1ULL << ReentPreParser::DefOtherPragma)
            | (1ULL << ReentPreParser::Introduce)
            | (1ULL << ReentPreParser::MetaSentence)
            | (1ULL << ReentPreParser::Stop)
            | (1ULL << ReentPreParser::PreprocPasses)
            | (1ULL << ReentPreParser::AddScan)
            | (1ULL << ReentPreParser::Scan)
            | (1ULL << ReentPreParser::AddParse)
            | (1ULL << ReentPreParser::Parse)
            | (1ULL << ReentPreParser::DefPattern)
            | (1ULL << ReentPreParser::DefXPath)
            | (1ULL << ReentPreParser::Line)
            | (1ULL << ReentPreParser::MultiLineMacro)
            | (1ULL << ReentPreParser::Directive)
            | (1ULL << ReentPreParser::AtValue)
            | (1ULL << ReentPreParser::Cilk_spawn)
            | (1ULL << ReentPreParser::Cilk_sync)
            | (1ULL << ReentPreParser::Conditions)
            | (1ULL << ReentPreParser::Controlled)
            | (1ULL << ReentPreParser::Div_)
            | (1ULL << ReentPreParser::False_)
            | (1ULL << ReentPreParser::Feed_forward)
            | (1ULL << ReentPreParser::GetText)
            | (1ULL << ReentPreParser::Goal)
            | (1ULL << ReentPreParser::Lin_extrapolator)
            | (1ULL << ReentPreParser::Mgua)
            | (1ULL << ReentPreParser::Mod_)
            | (1ULL << ReentPreParser::Nullptr)
            | (1ULL << ReentPreParser::Regexp_analyze)
            | (1ULL << ReentPreParser::Regexp_begin)
            | (1ULL << ReentPreParser::Regexp_end)
            | (1ULL << ReentPreParser::Regexp_parallel)
            | (1ULL << ReentPreParser::Regexp_sequential)
            | (1ULL << ReentPreParser::Rem)
            | (1ULL << ReentPreParser::True_)
            | (1ULL << ReentPreParser::Plc_regexp_var)
            | (1ULL << ReentPreParser::Plc_regexp_equal)
            | (1ULL << ReentPreParser::Plc_regexp_not_equal)
            | (1ULL << ReentPreParser::Plc_regexp_query)
            | (1ULL << ReentPreParser::LeftParen)
            | (1ULL << ReentPreParser::LeftBracket)
            | (1ULL << ReentPreParser::LeftBrace)
            | (1ULL << ReentPreParser::RightBrace)
            | (1ULL << ReentPreParser::AssignGreater)
            | (1ULL << ReentPreParser::DivDiv)
            | (1ULL << ReentPreParser::Pound)
            | (1ULL << ReentPreParser::And_)
            | (1ULL << ReentPreParser::Or_))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 64)) & ((1ULL << (ReentPreParser::At - 64))
            | (1ULL << (ReentPreParser::Is - 64))
            | (1ULL << (ReentPreParser::Is_ - 64))
            | (1ULL << (ReentPreParser::Prolog_not - 64))
            | (1ULL << (ReentPreParser::Prolog_not_equal - 64))
            | (1ULL << (ReentPreParser::Slash - 64))
            | (1ULL << (ReentPreParser::ConstructAtom - 64))
            | (1ULL << (ReentPreParser::Regexp_ref - 64))
            | (1ULL << (ReentPreParser::Underscore - 64))
            | (1ULL << (ReentPreParser::Plus - 64))
            | (1ULL << (ReentPreParser::Minus - 64))
            | (1ULL << (ReentPreParser::Star - 64))
            | (1ULL << (ReentPreParser::Div - 64))
            | (1ULL << (ReentPreParser::Mod - 64))
            | (1ULL << (ReentPreParser::Caret - 64))
            | (1ULL << (ReentPreParser::And - 64))
            | (1ULL << (ReentPreParser::Or - 64))
            | (1ULL << (ReentPreParser::Tilde - 64))
            | (1ULL << (ReentPreParser::Not - 64))
            | (1ULL << (ReentPreParser::Assign - 64))
            | (1ULL << (ReentPreParser::Less - 64))
            | (1ULL << (ReentPreParser::Greater - 64))
            | (1ULL << (ReentPreParser::Equal - 64))
            | (1ULL << (ReentPreParser::NotEqual - 64))
            | (1ULL << (ReentPreParser::LessEqual - 64))
            | (1ULL << (ReentPreParser::GreaterEqual - 64))
            | (1ULL << (ReentPreParser::AndAnd - 64))
            | (1ULL << (ReentPreParser::OrOr - 64))
            | (1ULL << (ReentPreParser::Arrow - 64))
            | (1ULL << (ReentPreParser::Question - 64))
            | (1ULL << (ReentPreParser::Colon - 64))
            | (1ULL << (ReentPreParser::Doublecolon - 64))
            | (1ULL << (ReentPreParser::Semi - 64))
            | (1ULL << (ReentPreParser::Dot - 64))
            | (1ULL << (ReentPreParser::DotStar - 64))
            | (1ULL << (ReentPreParser::Ellipsis - 64))
            | (1ULL << (ReentPreParser::Identifier - 64))
            | (1ULL << (ReentPreParser::DecimalLiteral - 64))
            | (1ULL << (ReentPreParser::OctalLiteral - 64))
            | (1ULL << (ReentPreParser::HexadecimalLiteral - 64))
            | (1ULL << (ReentPreParser::BinaryLiteral - 64))
            | (1ULL << (ReentPreParser::Integersuffix - 64))
            | (1ULL << (ReentPreParser::UserDefinedIntegerLiteral - 64))
            | (1ULL << (ReentPreParser::UserDefinedFloatingLiteral - 64))
            | (1ULL << (ReentPreParser::UserDefinedStringLiteral - 64))
            | (1ULL << (ReentPreParser::UserDefinedCharacterLiteral - 64))
            | (1ULL << (ReentPreParser::Whitespace - 64))
            | (1ULL << (ReentPreParser::Newline - 64))
            | (1ULL << (ReentPreParser::BlockComment - 64))
            | (1ULL << (ReentPreParser::LineComment - 64))
            | (1ULL << (ReentPreParser::PrologComment - 64)))) != 0)) {
            setState(1034);
            cpp_balanced_expression();
            setState(1039);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == ReentPreParser::Comma) {
              setState(1035);
              match(ReentPreParser::Comma);
              setState(1036);
              cpp_balanced_expression();
              setState(1041);
              _errHandler->sync(this);
              _la = _input->LA(1);
            }
          }
          setState(1044);
          match(ReentPreParser::RightParen);
          break;
        }

        default:
          break;
        }
        break;
      }

      case ReentPreParser::Regexp_fragment:
      case ReentPreParser::Regexp_set:
      case ReentPreParser::IntegerLiteral:
      case ReentPreParser::CharacterLiteral:
      case ReentPreParser::FloatingLiteral:
      case ReentPreParser::StringLiteral:
      case ReentPreParser::EmptyAtom:
      case ReentPreParser::BooleanLiteral:
      case ReentPreParser::PointerLiteral:
      case ReentPreParser::UserDefinedLiteral:
      case ReentPreParser::DefModule:
      case ReentPreParser::DefMemoization:
      case ReentPreParser::DoNotCheck:
      case ReentPreParser::DefOtherPragma:
      case ReentPreParser::Introduce:
      case ReentPreParser::MetaSentence:
      case ReentPreParser::Stop:
      case ReentPreParser::PreprocPasses:
      case ReentPreParser::AddScan:
      case ReentPreParser::Scan:
      case ReentPreParser::AddParse:
      case ReentPreParser::Parse:
      case ReentPreParser::DefPattern:
      case ReentPreParser::DefXPath:
      case ReentPreParser::Line:
      case ReentPreParser::MultiLineMacro:
      case ReentPreParser::Directive:
      case ReentPreParser::AtValue:
      case ReentPreParser::Cilk_spawn:
      case ReentPreParser::Cilk_sync:
      case ReentPreParser::Conditions:
      case ReentPreParser::Controlled:
      case ReentPreParser::Div_:
      case ReentPreParser::False_:
      case ReentPreParser::Feed_forward:
      case ReentPreParser::GetText:
      case ReentPreParser::Goal:
      case ReentPreParser::Lin_extrapolator:
      case ReentPreParser::Mgua:
      case ReentPreParser::Mod_:
      case ReentPreParser::Nullptr:
      case ReentPreParser::Regexp_analyze:
      case ReentPreParser::Regexp_begin:
      case ReentPreParser::Regexp_end:
      case ReentPreParser::Regexp_parallel:
      case ReentPreParser::Regexp_sequential:
      case ReentPreParser::Rem:
      case ReentPreParser::True_:
      case ReentPreParser::Plc_regexp_var:
      case ReentPreParser::Plc_regexp_equal:
      case ReentPreParser::Plc_regexp_not_equal:
      case ReentPreParser::Plc_regexp_query:
      case ReentPreParser::LeftBrace:
      case ReentPreParser::RightBrace:
      case ReentPreParser::AssignGreater:
      case ReentPreParser::DivDiv:
      case ReentPreParser::Pound:
      case ReentPreParser::And_:
      case ReentPreParser::Or_:
      case ReentPreParser::At:
      case ReentPreParser::Is:
      case ReentPreParser::Is_:
      case ReentPreParser::Prolog_not:
      case ReentPreParser::Prolog_not_equal:
      case ReentPreParser::Slash:
      case ReentPreParser::ConstructAtom:
      case ReentPreParser::Regexp_ref:
      case ReentPreParser::Underscore:
      case ReentPreParser::Plus:
      case ReentPreParser::Minus:
      case ReentPreParser::Star:
      case ReentPreParser::Div:
      case ReentPreParser::Mod:
      case ReentPreParser::Caret:
      case ReentPreParser::And:
      case ReentPreParser::Or:
      case ReentPreParser::Tilde:
      case ReentPreParser::Not:
      case ReentPreParser::Assign:
      case ReentPreParser::Less:
      case ReentPreParser::Greater:
      case ReentPreParser::Equal:
      case ReentPreParser::NotEqual:
      case ReentPreParser::LessEqual:
      case ReentPreParser::GreaterEqual:
      case ReentPreParser::AndAnd:
      case ReentPreParser::OrOr:
      case ReentPreParser::Arrow:
      case ReentPreParser::Question:
      case ReentPreParser::Colon:
      case ReentPreParser::Doublecolon:
      case ReentPreParser::Semi:
      case ReentPreParser::Dot:
      case ReentPreParser::DotStar:
      case ReentPreParser::Ellipsis:
      case ReentPreParser::DecimalLiteral:
      case ReentPreParser::OctalLiteral:
      case ReentPreParser::HexadecimalLiteral:
      case ReentPreParser::BinaryLiteral:
      case ReentPreParser::Integersuffix:
      case ReentPreParser::UserDefinedIntegerLiteral:
      case ReentPreParser::UserDefinedFloatingLiteral:
      case ReentPreParser::UserDefinedStringLiteral:
      case ReentPreParser::UserDefinedCharacterLiteral:
      case ReentPreParser::Whitespace:
      case ReentPreParser::Newline:
      case ReentPreParser::BlockComment:
      case ReentPreParser::LineComment:
      case ReentPreParser::PrologComment: {
        setState(1048); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(1047);
                  _la = _input->LA(1);
                  if (_la == 0 || _la == Token::EOF || (((((_la - 53) & ~ 0x3fULL) == 0) &&
                    ((1ULL << (_la - 53)) & ((1ULL << (ReentPreParser::LeftParen - 53))
                    | (1ULL << (ReentPreParser::RightParen - 53))
                    | (1ULL << (ReentPreParser::LeftBracket - 53))
                    | (1ULL << (ReentPreParser::RightBracket - 53))
                    | (1ULL << (ReentPreParser::Comma - 53))
                    | (1ULL << (ReentPreParser::Identifier - 53)))) != 0))) {
                  _errHandler->recoverInline(this);
                  }
                  else {
                    _errHandler->reportMatch(this);
                    consume();
                  }
                  break;
                }

          default:
            throw NoViableAltException(this);
          }
          setState(1050); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 150, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      case ReentPreParser::LeftParen: {
        setState(1052);
        match(ReentPreParser::LeftParen);
        setState(1053);
        cpp_balanced_expression();
        setState(1054);
        match(ReentPreParser::RightParen);
        break;
      }

      case ReentPreParser::LeftBracket: {
        setState(1056);
        match(ReentPreParser::LeftBracket);
        setState(1057);
        cpp_balanced_expression();
        setState(1058);
        match(ReentPreParser::RightBracket);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(1063);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ReentPreParser::Regexp_fragment)
      | (1ULL << ReentPreParser::Regexp_set)
      | (1ULL << ReentPreParser::IntegerLiteral)
      | (1ULL << ReentPreParser::CharacterLiteral)
      | (1ULL << ReentPreParser::FloatingLiteral)
      | (1ULL << ReentPreParser::StringLiteral)
      | (1ULL << ReentPreParser::EmptyAtom)
      | (1ULL << ReentPreParser::BooleanLiteral)
      | (1ULL << ReentPreParser::PointerLiteral)
      | (1ULL << ReentPreParser::UserDefinedLiteral)
      | (1ULL << ReentPreParser::DefModule)
      | (1ULL << ReentPreParser::DefMemoization)
      | (1ULL << ReentPreParser::DoNotCheck)
      | (1ULL << ReentPreParser::DefOtherPragma)
      | (1ULL << ReentPreParser::Introduce)
      | (1ULL << ReentPreParser::MetaSentence)
      | (1ULL << ReentPreParser::Stop)
      | (1ULL << ReentPreParser::PreprocPasses)
      | (1ULL << ReentPreParser::AddScan)
      | (1ULL << ReentPreParser::Scan)
      | (1ULL << ReentPreParser::AddParse)
      | (1ULL << ReentPreParser::Parse)
      | (1ULL << ReentPreParser::DefPattern)
      | (1ULL << ReentPreParser::DefXPath)
      | (1ULL << ReentPreParser::Line)
      | (1ULL << ReentPreParser::MultiLineMacro)
      | (1ULL << ReentPreParser::Directive)
      | (1ULL << ReentPreParser::AtValue)
      | (1ULL << ReentPreParser::Cilk_spawn)
      | (1ULL << ReentPreParser::Cilk_sync)
      | (1ULL << ReentPreParser::Conditions)
      | (1ULL << ReentPreParser::Controlled)
      | (1ULL << ReentPreParser::Div_)
      | (1ULL << ReentPreParser::False_)
      | (1ULL << ReentPreParser::Feed_forward)
      | (1ULL << ReentPreParser::GetText)
      | (1ULL << ReentPreParser::Goal)
      | (1ULL << ReentPreParser::Lin_extrapolator)
      | (1ULL << ReentPreParser::Mgua)
      | (1ULL << ReentPreParser::Mod_)
      | (1ULL << ReentPreParser::Nullptr)
      | (1ULL << ReentPreParser::Regexp_analyze)
      | (1ULL << ReentPreParser::Regexp_begin)
      | (1ULL << ReentPreParser::Regexp_end)
      | (1ULL << ReentPreParser::Regexp_parallel)
      | (1ULL << ReentPreParser::Regexp_sequential)
      | (1ULL << ReentPreParser::Rem)
      | (1ULL << ReentPreParser::True_)
      | (1ULL << ReentPreParser::Plc_regexp_var)
      | (1ULL << ReentPreParser::Plc_regexp_equal)
      | (1ULL << ReentPreParser::Plc_regexp_not_equal)
      | (1ULL << ReentPreParser::Plc_regexp_query)
      | (1ULL << ReentPreParser::LeftParen)
      | (1ULL << ReentPreParser::LeftBracket)
      | (1ULL << ReentPreParser::LeftBrace)
      | (1ULL << ReentPreParser::RightBrace)
      | (1ULL << ReentPreParser::AssignGreater)
      | (1ULL << ReentPreParser::DivDiv)
      | (1ULL << ReentPreParser::Pound)
      | (1ULL << ReentPreParser::And_)
      | (1ULL << ReentPreParser::Or_))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (ReentPreParser::At - 64))
      | (1ULL << (ReentPreParser::Is - 64))
      | (1ULL << (ReentPreParser::Is_ - 64))
      | (1ULL << (ReentPreParser::Prolog_not - 64))
      | (1ULL << (ReentPreParser::Prolog_not_equal - 64))
      | (1ULL << (ReentPreParser::Slash - 64))
      | (1ULL << (ReentPreParser::ConstructAtom - 64))
      | (1ULL << (ReentPreParser::Regexp_ref - 64))
      | (1ULL << (ReentPreParser::Underscore - 64))
      | (1ULL << (ReentPreParser::Plus - 64))
      | (1ULL << (ReentPreParser::Minus - 64))
      | (1ULL << (ReentPreParser::Star - 64))
      | (1ULL << (ReentPreParser::Div - 64))
      | (1ULL << (ReentPreParser::Mod - 64))
      | (1ULL << (ReentPreParser::Caret - 64))
      | (1ULL << (ReentPreParser::And - 64))
      | (1ULL << (ReentPreParser::Or - 64))
      | (1ULL << (ReentPreParser::Tilde - 64))
      | (1ULL << (ReentPreParser::Not - 64))
      | (1ULL << (ReentPreParser::Assign - 64))
      | (1ULL << (ReentPreParser::Less - 64))
      | (1ULL << (ReentPreParser::Greater - 64))
      | (1ULL << (ReentPreParser::Equal - 64))
      | (1ULL << (ReentPreParser::NotEqual - 64))
      | (1ULL << (ReentPreParser::LessEqual - 64))
      | (1ULL << (ReentPreParser::GreaterEqual - 64))
      | (1ULL << (ReentPreParser::AndAnd - 64))
      | (1ULL << (ReentPreParser::OrOr - 64))
      | (1ULL << (ReentPreParser::Arrow - 64))
      | (1ULL << (ReentPreParser::Question - 64))
      | (1ULL << (ReentPreParser::Colon - 64))
      | (1ULL << (ReentPreParser::Doublecolon - 64))
      | (1ULL << (ReentPreParser::Semi - 64))
      | (1ULL << (ReentPreParser::Dot - 64))
      | (1ULL << (ReentPreParser::DotStar - 64))
      | (1ULL << (ReentPreParser::Ellipsis - 64))
      | (1ULL << (ReentPreParser::Identifier - 64))
      | (1ULL << (ReentPreParser::DecimalLiteral - 64))
      | (1ULL << (ReentPreParser::OctalLiteral - 64))
      | (1ULL << (ReentPreParser::HexadecimalLiteral - 64))
      | (1ULL << (ReentPreParser::BinaryLiteral - 64))
      | (1ULL << (ReentPreParser::Integersuffix - 64))
      | (1ULL << (ReentPreParser::UserDefinedIntegerLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedFloatingLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedStringLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedCharacterLiteral - 64))
      | (1ULL << (ReentPreParser::Whitespace - 64))
      | (1ULL << (ReentPreParser::Newline - 64))
      | (1ULL << (ReentPreParser::BlockComment - 64))
      | (1ULL << (ReentPreParser::LineComment - 64))
      | (1ULL << (ReentPreParser::PrologComment - 64)))) != 0)) {
      setState(1062);
      cpp_balanced_expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MemoizationStyleContext ------------------------------------------------------------------

ReentPreParser::MemoizationStyleContext::MemoizationStyleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::MguaContext* ReentPreParser::MemoizationStyleContext::mgua() {
  return getRuleContext<ReentPreParser::MguaContext>(0);
}

ReentPreParser::NnetContext* ReentPreParser::MemoizationStyleContext::nnet() {
  return getRuleContext<ReentPreParser::NnetContext>(0);
}

ReentPreParser::ExtrapolatorContext* ReentPreParser::MemoizationStyleContext::extrapolator() {
  return getRuleContext<ReentPreParser::ExtrapolatorContext>(0);
}

ReentPreParser::ControlPredicateContext* ReentPreParser::MemoizationStyleContext::controlPredicate() {
  return getRuleContext<ReentPreParser::ControlPredicateContext>(0);
}


size_t ReentPreParser::MemoizationStyleContext::getRuleIndex() const {
  return ReentPreParser::RuleMemoizationStyle;
}

void ReentPreParser::MemoizationStyleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMemoizationStyle(this);
}

void ReentPreParser::MemoizationStyleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMemoizationStyle(this);
}

ReentPreParser::MemoizationStyleContext* ReentPreParser::memoizationStyle() {
  MemoizationStyleContext *_localctx = _tracker.createInstance<MemoizationStyleContext>(_ctx, getState());
  enterRule(_localctx, 106, ReentPreParser::RuleMemoizationStyle);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1068);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Mgua: {
        setState(1065);
        mgua();
        break;
      }

      case ReentPreParser::Feed_forward: {
        setState(1066);
        nnet();
        break;
      }

      case ReentPreParser::Lin_extrapolator: {
        setState(1067);
        extrapolator();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(1071);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Conditions

    || _la == ReentPreParser::Controlled) {
      setState(1070);
      controlPredicate();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MguaContext ------------------------------------------------------------------

ReentPreParser::MguaContext::MguaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::MguaContext::Mgua() {
  return getToken(ReentPreParser::Mgua, 0);
}

tree::TerminalNode* ReentPreParser::MguaContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::MguaContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

tree::TerminalNode* ReentPreParser::MguaContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::MguaContext::IntegerLiteral() {
  return getToken(ReentPreParser::IntegerLiteral, 0);
}

tree::TerminalNode* ReentPreParser::MguaContext::FloatingLiteral() {
  return getToken(ReentPreParser::FloatingLiteral, 0);
}


size_t ReentPreParser::MguaContext::getRuleIndex() const {
  return ReentPreParser::RuleMgua;
}

void ReentPreParser::MguaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMgua(this);
}

void ReentPreParser::MguaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMgua(this);
}

ReentPreParser::MguaContext* ReentPreParser::mgua() {
  MguaContext *_localctx = _tracker.createInstance<MguaContext>(_ctx, getState());
  enterRule(_localctx, 108, ReentPreParser::RuleMgua);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1073);
    match(ReentPreParser::Mgua);
    setState(1074);
    match(ReentPreParser::LeftParen);
    setState(1075);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::IntegerLiteral

    || _la == ReentPreParser::FloatingLiteral || _la == ReentPreParser::Identifier)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(1076);
    match(ReentPreParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NnetContext ------------------------------------------------------------------

ReentPreParser::NnetContext::NnetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::NnetContext::Feed_forward() {
  return getToken(ReentPreParser::Feed_forward, 0);
}

tree::TerminalNode* ReentPreParser::NnetContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::NnetContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::NnetContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}

tree::TerminalNode* ReentPreParser::NnetContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::NnetContext::IntegerLiteral() {
  return getTokens(ReentPreParser::IntegerLiteral);
}

tree::TerminalNode* ReentPreParser::NnetContext::IntegerLiteral(size_t i) {
  return getToken(ReentPreParser::IntegerLiteral, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::NnetContext::FloatingLiteral() {
  return getTokens(ReentPreParser::FloatingLiteral);
}

tree::TerminalNode* ReentPreParser::NnetContext::FloatingLiteral(size_t i) {
  return getToken(ReentPreParser::FloatingLiteral, i);
}

std::vector<ReentPreParser::Nnet_layer_specifierContext *> ReentPreParser::NnetContext::nnet_layer_specifier() {
  return getRuleContexts<ReentPreParser::Nnet_layer_specifierContext>();
}

ReentPreParser::Nnet_layer_specifierContext* ReentPreParser::NnetContext::nnet_layer_specifier(size_t i) {
  return getRuleContext<ReentPreParser::Nnet_layer_specifierContext>(i);
}


size_t ReentPreParser::NnetContext::getRuleIndex() const {
  return ReentPreParser::RuleNnet;
}

void ReentPreParser::NnetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNnet(this);
}

void ReentPreParser::NnetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNnet(this);
}

ReentPreParser::NnetContext* ReentPreParser::nnet() {
  NnetContext *_localctx = _tracker.createInstance<NnetContext>(_ctx, getState());
  enterRule(_localctx, 110, ReentPreParser::RuleNnet);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1078);
    match(ReentPreParser::Feed_forward);
    setState(1079);
    match(ReentPreParser::LeftParen);
    setState(1080);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::IntegerLiteral

    || _la == ReentPreParser::FloatingLiteral)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(1081);
    match(ReentPreParser::Comma);

    setState(1082);
    match(ReentPreParser::FloatingLiteral);
    setState(1083);
    match(ReentPreParser::Comma);

    setState(1084);
    match(ReentPreParser::IntegerLiteral);
    setState(1091);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Comma) {
      setState(1085);
      match(ReentPreParser::Comma);
      setState(1086);
      nnet_layer_specifier();
      setState(1089);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Comma) {
        setState(1087);
        match(ReentPreParser::Comma);
        setState(1088);
        nnet_layer_specifier();
      }
    }
    setState(1093);
    match(ReentPreParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExtrapolatorContext ------------------------------------------------------------------

ReentPreParser::ExtrapolatorContext::ExtrapolatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::ExtrapolatorContext::Lin_extrapolator() {
  return getToken(ReentPreParser::Lin_extrapolator, 0);
}

tree::TerminalNode* ReentPreParser::ExtrapolatorContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::ExtrapolatorContext::Comma() {
  return getToken(ReentPreParser::Comma, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::ExtrapolatorContext::IntegerLiteral() {
  return getTokens(ReentPreParser::IntegerLiteral);
}

tree::TerminalNode* ReentPreParser::ExtrapolatorContext::IntegerLiteral(size_t i) {
  return getToken(ReentPreParser::IntegerLiteral, i);
}

tree::TerminalNode* ReentPreParser::ExtrapolatorContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

tree::TerminalNode* ReentPreParser::ExtrapolatorContext::FloatingLiteral() {
  return getToken(ReentPreParser::FloatingLiteral, 0);
}


size_t ReentPreParser::ExtrapolatorContext::getRuleIndex() const {
  return ReentPreParser::RuleExtrapolator;
}

void ReentPreParser::ExtrapolatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExtrapolator(this);
}

void ReentPreParser::ExtrapolatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExtrapolator(this);
}

ReentPreParser::ExtrapolatorContext* ReentPreParser::extrapolator() {
  ExtrapolatorContext *_localctx = _tracker.createInstance<ExtrapolatorContext>(_ctx, getState());
  enterRule(_localctx, 112, ReentPreParser::RuleExtrapolator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1095);
    match(ReentPreParser::Lin_extrapolator);
    setState(1096);
    match(ReentPreParser::LeftParen);
    setState(1097);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::IntegerLiteral

    || _la == ReentPreParser::FloatingLiteral)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(1098);
    match(ReentPreParser::Comma);
    setState(1099);
    match(ReentPreParser::IntegerLiteral);
    setState(1100);
    match(ReentPreParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Nnet_layer_specifierContext ------------------------------------------------------------------

ReentPreParser::Nnet_layer_specifierContext::Nnet_layer_specifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Nnet_layer_specifierContext::IntegerLiteral() {
  return getToken(ReentPreParser::IntegerLiteral, 0);
}

tree::TerminalNode* ReentPreParser::Nnet_layer_specifierContext::Comma() {
  return getToken(ReentPreParser::Comma, 0);
}

ReentPreParser::Nnet_layer_typeContext* ReentPreParser::Nnet_layer_specifierContext::nnet_layer_type() {
  return getRuleContext<ReentPreParser::Nnet_layer_typeContext>(0);
}


size_t ReentPreParser::Nnet_layer_specifierContext::getRuleIndex() const {
  return ReentPreParser::RuleNnet_layer_specifier;
}

void ReentPreParser::Nnet_layer_specifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNnet_layer_specifier(this);
}

void ReentPreParser::Nnet_layer_specifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNnet_layer_specifier(this);
}

ReentPreParser::Nnet_layer_specifierContext* ReentPreParser::nnet_layer_specifier() {
  Nnet_layer_specifierContext *_localctx = _tracker.createInstance<Nnet_layer_specifierContext>(_ctx, getState());
  enterRule(_localctx, 114, ReentPreParser::RuleNnet_layer_specifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1102);
    match(ReentPreParser::IntegerLiteral);
    setState(1103);
    match(ReentPreParser::Comma);
    setState(1104);
    nnet_layer_type();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Nnet_layer_typeContext ------------------------------------------------------------------

ReentPreParser::Nnet_layer_typeContext::Nnet_layer_typeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Nnet_layer_typeContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}


size_t ReentPreParser::Nnet_layer_typeContext::getRuleIndex() const {
  return ReentPreParser::RuleNnet_layer_type;
}

void ReentPreParser::Nnet_layer_typeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNnet_layer_type(this);
}

void ReentPreParser::Nnet_layer_typeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNnet_layer_type(this);
}

ReentPreParser::Nnet_layer_typeContext* ReentPreParser::nnet_layer_type() {
  Nnet_layer_typeContext *_localctx = _tracker.createInstance<Nnet_layer_typeContext>(_ctx, getState());
  enterRule(_localctx, 116, ReentPreParser::RuleNnet_layer_type);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1109);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 157, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1106);

      if (!( _input->LT(1)->getText() == "e" || _input->LT(1)->getText() == "l" ||
      	  _input->LT(1)->getText() == "h" || _input->LT(1)->getText() == "r" )) throw FailedPredicateException(this, " _input->LT(1)->getText() == \"e\" || _input->LT(1)->getText() == \"l\" ||\n\t  _input->LT(1)->getText() == \"h\" || _input->LT(1)->getText() == \"r\" ");
      setState(1107);
      match(ReentPreParser::Identifier);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
       throw FailedPredicateException(this,
      		std::string("Must be the Number of neurons with following one of ['e','l','h','r']")); 
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ControlPredicateContext ------------------------------------------------------------------

ReentPreParser::ControlPredicateContext::ControlPredicateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::Automated_controlContext* ReentPreParser::ControlPredicateContext::automated_control() {
  return getRuleContext<ReentPreParser::Automated_controlContext>(0);
}

ReentPreParser::By_conditions_controlContext* ReentPreParser::ControlPredicateContext::by_conditions_control() {
  return getRuleContext<ReentPreParser::By_conditions_controlContext>(0);
}


size_t ReentPreParser::ControlPredicateContext::getRuleIndex() const {
  return ReentPreParser::RuleControlPredicate;
}

void ReentPreParser::ControlPredicateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterControlPredicate(this);
}

void ReentPreParser::ControlPredicateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitControlPredicate(this);
}

ReentPreParser::ControlPredicateContext* ReentPreParser::controlPredicate() {
  ControlPredicateContext *_localctx = _tracker.createInstance<ControlPredicateContext>(_ctx, getState());
  enterRule(_localctx, 118, ReentPreParser::RuleControlPredicate);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1113);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Controlled: {
        enterOuterAlt(_localctx, 1);
        setState(1111);
        automated_control();
        break;
      }

      case ReentPreParser::Conditions: {
        enterOuterAlt(_localctx, 2);
        setState(1112);
        by_conditions_control();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Automated_controlContext ------------------------------------------------------------------

ReentPreParser::Automated_controlContext::Automated_controlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Automated_controlContext::Controlled() {
  return getToken(ReentPreParser::Controlled, 0);
}

tree::TerminalNode* ReentPreParser::Automated_controlContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Automated_controlContext::IntegerLiteral() {
  return getTokens(ReentPreParser::IntegerLiteral);
}

tree::TerminalNode* ReentPreParser::Automated_controlContext::IntegerLiteral(size_t i) {
  return getToken(ReentPreParser::IntegerLiteral, i);
}

tree::TerminalNode* ReentPreParser::Automated_controlContext::Comma() {
  return getToken(ReentPreParser::Comma, 0);
}

tree::TerminalNode* ReentPreParser::Automated_controlContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}


size_t ReentPreParser::Automated_controlContext::getRuleIndex() const {
  return ReentPreParser::RuleAutomated_control;
}

void ReentPreParser::Automated_controlContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAutomated_control(this);
}

void ReentPreParser::Automated_controlContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAutomated_control(this);
}

ReentPreParser::Automated_controlContext* ReentPreParser::automated_control() {
  Automated_controlContext *_localctx = _tracker.createInstance<Automated_controlContext>(_ctx, getState());
  enterRule(_localctx, 120, ReentPreParser::RuleAutomated_control);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1115);
    match(ReentPreParser::Controlled);
    setState(1116);
    match(ReentPreParser::LeftParen);
    setState(1117);
    match(ReentPreParser::IntegerLiteral);
    setState(1118);
    match(ReentPreParser::Comma);
    setState(1119);
    match(ReentPreParser::IntegerLiteral);
    setState(1120);
    match(ReentPreParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- By_conditions_controlContext ------------------------------------------------------------------

ReentPreParser::By_conditions_controlContext::By_conditions_controlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::By_conditions_controlContext::Conditions() {
  return getToken(ReentPreParser::Conditions, 0);
}

tree::TerminalNode* ReentPreParser::By_conditions_controlContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

std::vector<ReentPreParser::Cpp_balanced_expressionContext *> ReentPreParser::By_conditions_controlContext::cpp_balanced_expression() {
  return getRuleContexts<ReentPreParser::Cpp_balanced_expressionContext>();
}

ReentPreParser::Cpp_balanced_expressionContext* ReentPreParser::By_conditions_controlContext::cpp_balanced_expression(size_t i) {
  return getRuleContext<ReentPreParser::Cpp_balanced_expressionContext>(i);
}

tree::TerminalNode* ReentPreParser::By_conditions_controlContext::Comma() {
  return getToken(ReentPreParser::Comma, 0);
}

tree::TerminalNode* ReentPreParser::By_conditions_controlContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}


size_t ReentPreParser::By_conditions_controlContext::getRuleIndex() const {
  return ReentPreParser::RuleBy_conditions_control;
}

void ReentPreParser::By_conditions_controlContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBy_conditions_control(this);
}

void ReentPreParser::By_conditions_controlContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBy_conditions_control(this);
}

ReentPreParser::By_conditions_controlContext* ReentPreParser::by_conditions_control() {
  By_conditions_controlContext *_localctx = _tracker.createInstance<By_conditions_controlContext>(_ctx, getState());
  enterRule(_localctx, 122, ReentPreParser::RuleBy_conditions_control);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1122);
    match(ReentPreParser::Conditions);
    setState(1123);
    match(ReentPreParser::LeftParen);
    setState(1124);
    cpp_balanced_expression();
    setState(1125);
    match(ReentPreParser::Comma);
    setState(1126);
    cpp_balanced_expression();
    setState(1127);
    match(ReentPreParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockHeaderContext ------------------------------------------------------------------

ReentPreParser::BlockHeaderContext::BlockHeaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::BlockHeaderContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::BlockHeaderContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::BlockHeaderContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

tree::TerminalNode* ReentPreParser::BlockHeaderContext::LeftBrace() {
  return getToken(ReentPreParser::LeftBrace, 0);
}

std::vector<ReentPreParser::ParameterContext *> ReentPreParser::BlockHeaderContext::parameter() {
  return getRuleContexts<ReentPreParser::ParameterContext>();
}

ReentPreParser::ParameterContext* ReentPreParser::BlockHeaderContext::parameter(size_t i) {
  return getRuleContext<ReentPreParser::ParameterContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::BlockHeaderContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::BlockHeaderContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

std::vector<ReentPreParser::TypeItemContext *> ReentPreParser::BlockHeaderContext::typeItem() {
  return getRuleContexts<ReentPreParser::TypeItemContext>();
}

ReentPreParser::TypeItemContext* ReentPreParser::BlockHeaderContext::typeItem(size_t i) {
  return getRuleContext<ReentPreParser::TypeItemContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::BlockHeaderContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::BlockHeaderContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::BlockHeaderContext::getRuleIndex() const {
  return ReentPreParser::RuleBlockHeader;
}

void ReentPreParser::BlockHeaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBlockHeader(this);
}

void ReentPreParser::BlockHeaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBlockHeader(this);
}

ReentPreParser::BlockHeaderContext* ReentPreParser::blockHeader() {
  BlockHeaderContext *_localctx = _tracker.createInstance<BlockHeaderContext>(_ctx, getState());
  enterRule(_localctx, 124, ReentPreParser::RuleBlockHeader);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1130); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(1129);
              dynamic_cast<BlockHeaderContext *>(_localctx)->type = typeItem();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(1132); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 159, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(1134);
    match(ReentPreParser::Identifier);
    setState(1135);
    match(ReentPreParser::LeftParen);
     if ((dynamic_cast<BlockHeaderContext *>(_localctx)->type != nullptr ? _input->getText(dynamic_cast<BlockHeaderContext *>(_localctx)->type->start, dynamic_cast<BlockHeaderContext *>(_localctx)->type->stop) : nullptr) == "void" &&
    		std::find(memo_map.begin(), memo_map.end(), "o") == memo_map.end() &&
    		std::find(memo_map.begin(), memo_map.end(), "*o") == memo_map.end()
    		)
    		throw FailedPredicateException(this, "void memoized function must have 'o' parameter");
    	  else if ((dynamic_cast<BlockHeaderContext *>(_localctx)->type != nullptr ? _input->getText(dynamic_cast<BlockHeaderContext *>(_localctx)->type->start, dynamic_cast<BlockHeaderContext *>(_localctx)->type->stop) : nullptr) != "void" &&
    		( std::find(memo_map.begin(), memo_map.end(), "o") != memo_map.end() ||
    		std::find(memo_map.begin(), memo_map.end(), "*o") != memo_map.end())
    		)
    		throw FailedPredicateException(this, "non-void memoized function can't have 'o' parameter");
    	  int param_count = 0;
    	
    setState(1148);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Identifier) {
      setState(1137);
      parameter();
       param_count++; 
      setState(1145);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Comma) {
        setState(1139);
        match(ReentPreParser::Comma);
        setState(1140);
        parameter();
         param_count++; 
        setState(1147);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(1150);
    match(ReentPreParser::RightParen);
     if (param_count != memo_map.size()) throw FailedPredicateException(this, "number of mapping parameters does not correspond to the number of parameters in function's header"); 
    setState(1155);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(1152);
      match(ReentPreParser::Newline);
      setState(1157);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1158);
    match(ReentPreParser::LeftBrace);
    setState(1162);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ReentPreParser::Regexp_fragment)
      | (1ULL << ReentPreParser::Regexp_set)
      | (1ULL << ReentPreParser::IntegerLiteral)
      | (1ULL << ReentPreParser::CharacterLiteral)
      | (1ULL << ReentPreParser::FloatingLiteral)
      | (1ULL << ReentPreParser::StringLiteral)
      | (1ULL << ReentPreParser::EmptyAtom)
      | (1ULL << ReentPreParser::BooleanLiteral)
      | (1ULL << ReentPreParser::PointerLiteral)
      | (1ULL << ReentPreParser::UserDefinedLiteral)
      | (1ULL << ReentPreParser::DefModule)
      | (1ULL << ReentPreParser::DefMemoization)
      | (1ULL << ReentPreParser::DoNotCheck)
      | (1ULL << ReentPreParser::DefOtherPragma)
      | (1ULL << ReentPreParser::Introduce)
      | (1ULL << ReentPreParser::MetaSentence)
      | (1ULL << ReentPreParser::Stop)
      | (1ULL << ReentPreParser::PreprocPasses)
      | (1ULL << ReentPreParser::AddScan)
      | (1ULL << ReentPreParser::Scan)
      | (1ULL << ReentPreParser::AddParse)
      | (1ULL << ReentPreParser::Parse)
      | (1ULL << ReentPreParser::DefPattern)
      | (1ULL << ReentPreParser::DefXPath)
      | (1ULL << ReentPreParser::Line)
      | (1ULL << ReentPreParser::MultiLineMacro)
      | (1ULL << ReentPreParser::Directive)
      | (1ULL << ReentPreParser::AtValue)
      | (1ULL << ReentPreParser::Cilk_spawn)
      | (1ULL << ReentPreParser::Cilk_sync)
      | (1ULL << ReentPreParser::Conditions)
      | (1ULL << ReentPreParser::Controlled)
      | (1ULL << ReentPreParser::Div_)
      | (1ULL << ReentPreParser::False_)
      | (1ULL << ReentPreParser::Feed_forward)
      | (1ULL << ReentPreParser::GetText)
      | (1ULL << ReentPreParser::Goal)
      | (1ULL << ReentPreParser::Lin_extrapolator)
      | (1ULL << ReentPreParser::Mgua)
      | (1ULL << ReentPreParser::Mod_)
      | (1ULL << ReentPreParser::Nullptr)
      | (1ULL << ReentPreParser::Regexp_analyze)
      | (1ULL << ReentPreParser::Regexp_begin)
      | (1ULL << ReentPreParser::Regexp_end)
      | (1ULL << ReentPreParser::Regexp_parallel)
      | (1ULL << ReentPreParser::Regexp_sequential)
      | (1ULL << ReentPreParser::Rem)
      | (1ULL << ReentPreParser::True_)
      | (1ULL << ReentPreParser::Plc_regexp_var)
      | (1ULL << ReentPreParser::Plc_regexp_equal)
      | (1ULL << ReentPreParser::Plc_regexp_not_equal)
      | (1ULL << ReentPreParser::Plc_regexp_query)
      | (1ULL << ReentPreParser::LeftParen)
      | (1ULL << ReentPreParser::RightParen)
      | (1ULL << ReentPreParser::LeftBracket)
      | (1ULL << ReentPreParser::RightBracket)
      | (1ULL << ReentPreParser::LeftBrace)
      | (1ULL << ReentPreParser::RightBrace)
      | (1ULL << ReentPreParser::AssignGreater)
      | (1ULL << ReentPreParser::DivDiv)
      | (1ULL << ReentPreParser::Pound)
      | (1ULL << ReentPreParser::And_)
      | (1ULL << ReentPreParser::Or_))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (ReentPreParser::At - 64))
      | (1ULL << (ReentPreParser::Is - 64))
      | (1ULL << (ReentPreParser::Is_ - 64))
      | (1ULL << (ReentPreParser::Prolog_not - 64))
      | (1ULL << (ReentPreParser::Prolog_not_equal - 64))
      | (1ULL << (ReentPreParser::Slash - 64))
      | (1ULL << (ReentPreParser::ConstructAtom - 64))
      | (1ULL << (ReentPreParser::Regexp_ref - 64))
      | (1ULL << (ReentPreParser::Underscore - 64))
      | (1ULL << (ReentPreParser::Plus - 64))
      | (1ULL << (ReentPreParser::Minus - 64))
      | (1ULL << (ReentPreParser::Star - 64))
      | (1ULL << (ReentPreParser::Div - 64))
      | (1ULL << (ReentPreParser::Mod - 64))
      | (1ULL << (ReentPreParser::Caret - 64))
      | (1ULL << (ReentPreParser::And - 64))
      | (1ULL << (ReentPreParser::Or - 64))
      | (1ULL << (ReentPreParser::Tilde - 64))
      | (1ULL << (ReentPreParser::Not - 64))
      | (1ULL << (ReentPreParser::Assign - 64))
      | (1ULL << (ReentPreParser::Less - 64))
      | (1ULL << (ReentPreParser::Greater - 64))
      | (1ULL << (ReentPreParser::Equal - 64))
      | (1ULL << (ReentPreParser::NotEqual - 64))
      | (1ULL << (ReentPreParser::LessEqual - 64))
      | (1ULL << (ReentPreParser::GreaterEqual - 64))
      | (1ULL << (ReentPreParser::AndAnd - 64))
      | (1ULL << (ReentPreParser::OrOr - 64))
      | (1ULL << (ReentPreParser::Comma - 64))
      | (1ULL << (ReentPreParser::Arrow - 64))
      | (1ULL << (ReentPreParser::Question - 64))
      | (1ULL << (ReentPreParser::Colon - 64))
      | (1ULL << (ReentPreParser::Doublecolon - 64))
      | (1ULL << (ReentPreParser::Semi - 64))
      | (1ULL << (ReentPreParser::Dot - 64))
      | (1ULL << (ReentPreParser::DotStar - 64))
      | (1ULL << (ReentPreParser::Ellipsis - 64))
      | (1ULL << (ReentPreParser::Identifier - 64))
      | (1ULL << (ReentPreParser::DecimalLiteral - 64))
      | (1ULL << (ReentPreParser::OctalLiteral - 64))
      | (1ULL << (ReentPreParser::HexadecimalLiteral - 64))
      | (1ULL << (ReentPreParser::BinaryLiteral - 64))
      | (1ULL << (ReentPreParser::Integersuffix - 64))
      | (1ULL << (ReentPreParser::UserDefinedIntegerLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedFloatingLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedStringLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedCharacterLiteral - 64))
      | (1ULL << (ReentPreParser::Whitespace - 64))
      | (1ULL << (ReentPreParser::BlockComment - 64))
      | (1ULL << (ReentPreParser::LineComment - 64))
      | (1ULL << (ReentPreParser::PrologComment - 64)))) != 0)) {
      setState(1159);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == ReentPreParser::Newline)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1164);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1166); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(1165);
              match(ReentPreParser::Newline);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(1168); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 164, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeItemContext ------------------------------------------------------------------

ReentPreParser::TypeItemContext::TypeItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::TypeSpecifierContext* ReentPreParser::TypeItemContext::typeSpecifier() {
  return getRuleContext<ReentPreParser::TypeSpecifierContext>(0);
}

tree::TerminalNode* ReentPreParser::TypeItemContext::And() {
  return getToken(ReentPreParser::And, 0);
}

tree::TerminalNode* ReentPreParser::TypeItemContext::AndAnd() {
  return getToken(ReentPreParser::AndAnd, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::TypeItemContext::Star() {
  return getTokens(ReentPreParser::Star);
}

tree::TerminalNode* ReentPreParser::TypeItemContext::Star(size_t i) {
  return getToken(ReentPreParser::Star, i);
}


size_t ReentPreParser::TypeItemContext::getRuleIndex() const {
  return ReentPreParser::RuleTypeItem;
}

void ReentPreParser::TypeItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeItem(this);
}

void ReentPreParser::TypeItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeItem(this);
}

ReentPreParser::TypeItemContext* ReentPreParser::typeItem() {
  TypeItemContext *_localctx = _tracker.createInstance<TypeItemContext>(_ctx, getState());
  enterRule(_localctx, 126, ReentPreParser::RuleTypeItem);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1170);
    typeSpecifier();
    setState(1179);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::And: {
        setState(1171);
        match(ReentPreParser::And);
        break;
      }

      case ReentPreParser::AndAnd: {
        setState(1172);
        match(ReentPreParser::AndAnd);
        break;
      }

      case ReentPreParser::Star:
      case ReentPreParser::Identifier: {
        setState(1176);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ReentPreParser::Star) {
          setState(1173);
          match(ReentPreParser::Star);
          setState(1178);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeSpecifierContext ------------------------------------------------------------------

ReentPreParser::TypeSpecifierContext::TypeSpecifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ReentPreParser::TypeSpecifierContext::Identifier() {
  return getTokens(ReentPreParser::Identifier);
}

tree::TerminalNode* ReentPreParser::TypeSpecifierContext::Identifier(size_t i) {
  return getToken(ReentPreParser::Identifier, i);
}

tree::TerminalNode* ReentPreParser::TypeSpecifierContext::Less() {
  return getToken(ReentPreParser::Less, 0);
}

tree::TerminalNode* ReentPreParser::TypeSpecifierContext::Greater() {
  return getToken(ReentPreParser::Greater, 0);
}

ReentPreParser::TemplateParametersContext* ReentPreParser::TypeSpecifierContext::templateParameters() {
  return getRuleContext<ReentPreParser::TemplateParametersContext>(0);
}


size_t ReentPreParser::TypeSpecifierContext::getRuleIndex() const {
  return ReentPreParser::RuleTypeSpecifier;
}

void ReentPreParser::TypeSpecifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeSpecifier(this);
}

void ReentPreParser::TypeSpecifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeSpecifier(this);
}

ReentPreParser::TypeSpecifierContext* ReentPreParser::typeSpecifier() {
  TypeSpecifierContext *_localctx = _tracker.createInstance<TypeSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 128, ReentPreParser::RuleTypeSpecifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1181);
    match(ReentPreParser::Identifier);
    setState(1193);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Less: {
        setState(1182);
        match(ReentPreParser::Less);
        setState(1184);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << ReentPreParser::IntegerLiteral)
          | (1ULL << ReentPreParser::CharacterLiteral)
          | (1ULL << ReentPreParser::FloatingLiteral)
          | (1ULL << ReentPreParser::StringLiteral)
          | (1ULL << ReentPreParser::BooleanLiteral)
          | (1ULL << ReentPreParser::PointerLiteral)
          | (1ULL << ReentPreParser::UserDefinedLiteral))) != 0) || _la == ReentPreParser::Identifier) {
          setState(1183);
          templateParameters();
        }
        setState(1186);
        match(ReentPreParser::Greater);
        break;
      }

      case ReentPreParser::Star:
      case ReentPreParser::And:
      case ReentPreParser::Greater:
      case ReentPreParser::AndAnd:
      case ReentPreParser::Comma:
      case ReentPreParser::Identifier: {
        setState(1190);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 168, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(1187);
            match(ReentPreParser::Identifier); 
          }
          setState(1192);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 168, _ctx);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateParametersContext ------------------------------------------------------------------

ReentPreParser::TemplateParametersContext::TemplateParametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::TemplateParameterContext *> ReentPreParser::TemplateParametersContext::templateParameter() {
  return getRuleContexts<ReentPreParser::TemplateParameterContext>();
}

ReentPreParser::TemplateParameterContext* ReentPreParser::TemplateParametersContext::templateParameter(size_t i) {
  return getRuleContext<ReentPreParser::TemplateParameterContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::TemplateParametersContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::TemplateParametersContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::TemplateParametersContext::getRuleIndex() const {
  return ReentPreParser::RuleTemplateParameters;
}

void ReentPreParser::TemplateParametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateParameters(this);
}

void ReentPreParser::TemplateParametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateParameters(this);
}

ReentPreParser::TemplateParametersContext* ReentPreParser::templateParameters() {
  TemplateParametersContext *_localctx = _tracker.createInstance<TemplateParametersContext>(_ctx, getState());
  enterRule(_localctx, 130, ReentPreParser::RuleTemplateParameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1195);
    templateParameter();
    setState(1200);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(1196);
      match(ReentPreParser::Comma);
      setState(1197);
      templateParameter();
      setState(1202);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TemplateParameterContext ------------------------------------------------------------------

ReentPreParser::TemplateParameterContext::TemplateParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::TypeSpecifierContext* ReentPreParser::TemplateParameterContext::typeSpecifier() {
  return getRuleContext<ReentPreParser::TypeSpecifierContext>(0);
}

ReentPreParser::LiteralContext* ReentPreParser::TemplateParameterContext::literal() {
  return getRuleContext<ReentPreParser::LiteralContext>(0);
}


size_t ReentPreParser::TemplateParameterContext::getRuleIndex() const {
  return ReentPreParser::RuleTemplateParameter;
}

void ReentPreParser::TemplateParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTemplateParameter(this);
}

void ReentPreParser::TemplateParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTemplateParameter(this);
}

ReentPreParser::TemplateParameterContext* ReentPreParser::templateParameter() {
  TemplateParameterContext *_localctx = _tracker.createInstance<TemplateParameterContext>(_ctx, getState());
  enterRule(_localctx, 132, ReentPreParser::RuleTemplateParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1205);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(1203);
        typeSpecifier();
        break;
      }

      case ReentPreParser::IntegerLiteral:
      case ReentPreParser::CharacterLiteral:
      case ReentPreParser::FloatingLiteral:
      case ReentPreParser::StringLiteral:
      case ReentPreParser::BooleanLiteral:
      case ReentPreParser::PointerLiteral:
      case ReentPreParser::UserDefinedLiteral: {
        enterOuterAlt(_localctx, 2);
        setState(1204);
        literal();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterContext ------------------------------------------------------------------

ReentPreParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::TypeItemContext* ReentPreParser::ParameterContext::typeItem() {
  return getRuleContext<ReentPreParser::TypeItemContext>(0);
}

tree::TerminalNode* ReentPreParser::ParameterContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

std::vector<ReentPreParser::DimensionContext *> ReentPreParser::ParameterContext::dimension() {
  return getRuleContexts<ReentPreParser::DimensionContext>();
}

ReentPreParser::DimensionContext* ReentPreParser::ParameterContext::dimension(size_t i) {
  return getRuleContext<ReentPreParser::DimensionContext>(i);
}


size_t ReentPreParser::ParameterContext::getRuleIndex() const {
  return ReentPreParser::RuleParameter;
}

void ReentPreParser::ParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter(this);
}

void ReentPreParser::ParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter(this);
}

ReentPreParser::ParameterContext* ReentPreParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 134, ReentPreParser::RuleParameter);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1207);
    typeItem();
    setState(1208);
    match(ReentPreParser::Identifier);
    setState(1212);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::LeftBracket) {
      setState(1209);
      dimension();
      setState(1214);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DimensionContext ------------------------------------------------------------------

ReentPreParser::DimensionContext::DimensionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::DimensionContext::LeftBracket() {
  return getToken(ReentPreParser::LeftBracket, 0);
}

tree::TerminalNode* ReentPreParser::DimensionContext::RightBracket() {
  return getToken(ReentPreParser::RightBracket, 0);
}

tree::TerminalNode* ReentPreParser::DimensionContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::DimensionContext::IntegerLiteral() {
  return getToken(ReentPreParser::IntegerLiteral, 0);
}


size_t ReentPreParser::DimensionContext::getRuleIndex() const {
  return ReentPreParser::RuleDimension;
}

void ReentPreParser::DimensionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDimension(this);
}

void ReentPreParser::DimensionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDimension(this);
}

ReentPreParser::DimensionContext* ReentPreParser::dimension() {
  DimensionContext *_localctx = _tracker.createInstance<DimensionContext>(_ctx, getState());
  enterRule(_localctx, 136, ReentPreParser::RuleDimension);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1215);
    match(ReentPreParser::LeftBracket);
    setState(1216);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::IntegerLiteral || _la == ReentPreParser::Identifier)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(1217);
    match(ReentPreParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_goalContext ------------------------------------------------------------------

ReentPreParser::Prolog_goalContext::Prolog_goalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_goalContext::Goal() {
  return getToken(ReentPreParser::Goal, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_goalContext::Is() {
  return getToken(ReentPreParser::Is, 0);
}

ReentPreParser::Prolog_predicatesContext* ReentPreParser::Prolog_goalContext::prolog_predicates() {
  return getRuleContext<ReentPreParser::Prolog_predicatesContext>(0);
}

tree::TerminalNode* ReentPreParser::Prolog_goalContext::Dot() {
  return getToken(ReentPreParser::Dot, 0);
}


size_t ReentPreParser::Prolog_goalContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_goal;
}

void ReentPreParser::Prolog_goalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_goal(this);
}

void ReentPreParser::Prolog_goalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_goal(this);
}

ReentPreParser::Prolog_goalContext* ReentPreParser::prolog_goal() {
  Prolog_goalContext *_localctx = _tracker.createInstance<Prolog_goalContext>(_ctx, getState());
  enterRule(_localctx, 138, ReentPreParser::RuleProlog_goal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1219);
    match(ReentPreParser::Goal);
    setState(1220);
    match(ReentPreParser::Is);
    setState(1221);
    prolog_predicates();
    setState(1222);
    match(ReentPreParser::Dot);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_statementContext ------------------------------------------------------------------

ReentPreParser::Prolog_statementContext::Prolog_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_statementContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_statementContext::Dot() {
  return getToken(ReentPreParser::Dot, 0);
}

ReentPreParser::Prolog_parametersContext* ReentPreParser::Prolog_statementContext::prolog_parameters() {
  return getRuleContext<ReentPreParser::Prolog_parametersContext>(0);
}

tree::TerminalNode* ReentPreParser::Prolog_statementContext::Is() {
  return getToken(ReentPreParser::Is, 0);
}

ReentPreParser::Prolog_predicatesContext* ReentPreParser::Prolog_statementContext::prolog_predicates() {
  return getRuleContext<ReentPreParser::Prolog_predicatesContext>(0);
}


size_t ReentPreParser::Prolog_statementContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_statement;
}

void ReentPreParser::Prolog_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_statement(this);
}

void ReentPreParser::Prolog_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_statement(this);
}

ReentPreParser::Prolog_statementContext* ReentPreParser::prolog_statement() {
  Prolog_statementContext *_localctx = _tracker.createInstance<Prolog_statementContext>(_ctx, getState());
  enterRule(_localctx, 140, ReentPreParser::RuleProlog_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1224);
    match(ReentPreParser::Identifier);
    setState(1226);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftParen) {
      setState(1225);
      prolog_parameters();
    }
    setState(1230);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Is) {
      setState(1228);
      match(ReentPreParser::Is);
      setState(1229);
      prolog_predicates();
    }
    setState(1232);
    match(ReentPreParser::Dot);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_parametersContext ------------------------------------------------------------------

ReentPreParser::Prolog_parametersContext::Prolog_parametersContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_parametersContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

std::vector<ReentPreParser::Prolog_parameterContext *> ReentPreParser::Prolog_parametersContext::prolog_parameter() {
  return getRuleContexts<ReentPreParser::Prolog_parameterContext>();
}

ReentPreParser::Prolog_parameterContext* ReentPreParser::Prolog_parametersContext::prolog_parameter(size_t i) {
  return getRuleContext<ReentPreParser::Prolog_parameterContext>(i);
}

tree::TerminalNode* ReentPreParser::Prolog_parametersContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Prolog_parametersContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Prolog_parametersContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::Prolog_parametersContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_parameters;
}

void ReentPreParser::Prolog_parametersContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_parameters(this);
}

void ReentPreParser::Prolog_parametersContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_parameters(this);
}

ReentPreParser::Prolog_parametersContext* ReentPreParser::prolog_parameters() {
  Prolog_parametersContext *_localctx = _tracker.createInstance<Prolog_parametersContext>(_ctx, getState());
  enterRule(_localctx, 142, ReentPreParser::RuleProlog_parameters);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1234);
    match(ReentPreParser::LeftParen);
    setState(1235);
    prolog_parameter();
    setState(1240);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(1236);
      match(ReentPreParser::Comma);
      setState(1237);
      prolog_parameter();
      setState(1242);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1243);
    match(ReentPreParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_predicatesContext ------------------------------------------------------------------

ReentPreParser::Prolog_predicatesContext::Prolog_predicatesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::Prolog_predicateContext* ReentPreParser::Prolog_predicatesContext::prolog_predicate() {
  return getRuleContext<ReentPreParser::Prolog_predicateContext>(0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Prolog_predicatesContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Prolog_predicatesContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

tree::TerminalNode* ReentPreParser::Prolog_predicatesContext::Prolog_not() {
  return getToken(ReentPreParser::Prolog_not, 0);
}

ReentPreParser::Prolog_if_thenContext* ReentPreParser::Prolog_predicatesContext::prolog_if_then() {
  return getRuleContext<ReentPreParser::Prolog_if_thenContext>(0);
}

ReentPreParser::Prolog_predicatesContext* ReentPreParser::Prolog_predicatesContext::prolog_predicates() {
  return getRuleContext<ReentPreParser::Prolog_predicatesContext>(0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicatesContext::Semi() {
  return getToken(ReentPreParser::Semi, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicatesContext::Comma() {
  return getToken(ReentPreParser::Comma, 0);
}


size_t ReentPreParser::Prolog_predicatesContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_predicates;
}

void ReentPreParser::Prolog_predicatesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_predicates(this);
}

void ReentPreParser::Prolog_predicatesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_predicates(this);
}

ReentPreParser::Prolog_predicatesContext* ReentPreParser::prolog_predicates() {
  Prolog_predicatesContext *_localctx = _tracker.createInstance<Prolog_predicatesContext>(_ctx, getState());
  enterRule(_localctx, 144, ReentPreParser::RuleProlog_predicates);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1248);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(1245);
      match(ReentPreParser::Newline);
      setState(1250);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1252);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Prolog_not) {
      setState(1251);
      match(ReentPreParser::Prolog_not);
    }
    setState(1254);
    prolog_predicate();
    setState(1256);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Arrow) {
      setState(1255);
      prolog_if_then();
    }
    setState(1260);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Comma

    || _la == ReentPreParser::Semi) {
      setState(1258);
      _la = _input->LA(1);
      if (!(_la == ReentPreParser::Comma

      || _la == ReentPreParser::Semi)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1259);
      prolog_predicates();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_parameterContext ------------------------------------------------------------------

ReentPreParser::Prolog_parameterContext::Prolog_parameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::LiteralContext* ReentPreParser::Prolog_parameterContext::literal() {
  return getRuleContext<ReentPreParser::LiteralContext>(0);
}

tree::TerminalNode* ReentPreParser::Prolog_parameterContext::EmptyAtom() {
  return getToken(ReentPreParser::EmptyAtom, 0);
}

ReentPreParser::Prolog_parameter_listContext* ReentPreParser::Prolog_parameterContext::prolog_parameter_list() {
  return getRuleContext<ReentPreParser::Prolog_parameter_listContext>(0);
}

ReentPreParser::Prolog_predicateContext* ReentPreParser::Prolog_parameterContext::prolog_predicate() {
  return getRuleContext<ReentPreParser::Prolog_predicateContext>(0);
}

tree::TerminalNode* ReentPreParser::Prolog_parameterContext::Underscore() {
  return getToken(ReentPreParser::Underscore, 0);
}


size_t ReentPreParser::Prolog_parameterContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_parameter;
}

void ReentPreParser::Prolog_parameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_parameter(this);
}

void ReentPreParser::Prolog_parameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_parameter(this);
}

ReentPreParser::Prolog_parameterContext* ReentPreParser::prolog_parameter() {
  Prolog_parameterContext *_localctx = _tracker.createInstance<Prolog_parameterContext>(_ctx, getState());
  enterRule(_localctx, 146, ReentPreParser::RuleProlog_parameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1267);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 180, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1262);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1263);
      match(ReentPreParser::EmptyAtom);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1264);
      prolog_parameter_list();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(1265);
      prolog_predicate();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(1266);
      match(ReentPreParser::Underscore);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_parameter_listContext ------------------------------------------------------------------

ReentPreParser::Prolog_parameter_listContext::Prolog_parameter_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_parameter_listContext::LeftBracket() {
  return getToken(ReentPreParser::LeftBracket, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_parameter_listContext::RightBracket() {
  return getToken(ReentPreParser::RightBracket, 0);
}

ReentPreParser::Prolog_inside_listContext* ReentPreParser::Prolog_parameter_listContext::prolog_inside_list() {
  return getRuleContext<ReentPreParser::Prolog_inside_listContext>(0);
}

tree::TerminalNode* ReentPreParser::Prolog_parameter_listContext::Or() {
  return getToken(ReentPreParser::Or, 0);
}

ReentPreParser::Prolog_parameterContext* ReentPreParser::Prolog_parameter_listContext::prolog_parameter() {
  return getRuleContext<ReentPreParser::Prolog_parameterContext>(0);
}


size_t ReentPreParser::Prolog_parameter_listContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_parameter_list;
}

void ReentPreParser::Prolog_parameter_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_parameter_list(this);
}

void ReentPreParser::Prolog_parameter_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_parameter_list(this);
}

ReentPreParser::Prolog_parameter_listContext* ReentPreParser::prolog_parameter_list() {
  Prolog_parameter_listContext *_localctx = _tracker.createInstance<Prolog_parameter_listContext>(_ctx, getState());
  enterRule(_localctx, 148, ReentPreParser::RuleProlog_parameter_list);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1269);
    match(ReentPreParser::LeftBracket);
    setState(1275);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ReentPreParser::IntegerLiteral)
      | (1ULL << ReentPreParser::CharacterLiteral)
      | (1ULL << ReentPreParser::FloatingLiteral)
      | (1ULL << ReentPreParser::StringLiteral)
      | (1ULL << ReentPreParser::EmptyAtom)
      | (1ULL << ReentPreParser::BooleanLiteral)
      | (1ULL << ReentPreParser::PointerLiteral)
      | (1ULL << ReentPreParser::UserDefinedLiteral)
      | (1ULL << ReentPreParser::LeftParen)
      | (1ULL << ReentPreParser::LeftBracket))) != 0) || ((((_la - 68) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 68)) & ((1ULL << (ReentPreParser::Prolog_not_equal - 68))
      | (1ULL << (ReentPreParser::ConstructAtom - 68))
      | (1ULL << (ReentPreParser::Underscore - 68))
      | (1ULL << (ReentPreParser::Plus - 68))
      | (1ULL << (ReentPreParser::Minus - 68))
      | (1ULL << (ReentPreParser::Not - 68))
      | (1ULL << (ReentPreParser::Assign - 68))
      | (1ULL << (ReentPreParser::Less - 68))
      | (1ULL << (ReentPreParser::Greater - 68))
      | (1ULL << (ReentPreParser::Equal - 68))
      | (1ULL << (ReentPreParser::NotEqual - 68))
      | (1ULL << (ReentPreParser::LessEqual - 68))
      | (1ULL << (ReentPreParser::GreaterEqual - 68))
      | (1ULL << (ReentPreParser::Arrow - 68))
      | (1ULL << (ReentPreParser::Semi - 68))
      | (1ULL << (ReentPreParser::Identifier - 68)))) != 0)) {
      setState(1270);
      prolog_inside_list();
      setState(1273);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Or) {
        setState(1271);
        match(ReentPreParser::Or);
        setState(1272);
        prolog_parameter();
      }
    }
    setState(1277);
    match(ReentPreParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_inside_listContext ------------------------------------------------------------------

ReentPreParser::Prolog_inside_listContext::Prolog_inside_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::Prolog_parameterContext* ReentPreParser::Prolog_inside_listContext::prolog_parameter() {
  return getRuleContext<ReentPreParser::Prolog_parameterContext>(0);
}

tree::TerminalNode* ReentPreParser::Prolog_inside_listContext::Comma() {
  return getToken(ReentPreParser::Comma, 0);
}

ReentPreParser::Prolog_inside_listContext* ReentPreParser::Prolog_inside_listContext::prolog_inside_list() {
  return getRuleContext<ReentPreParser::Prolog_inside_listContext>(0);
}


size_t ReentPreParser::Prolog_inside_listContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_inside_list;
}

void ReentPreParser::Prolog_inside_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_inside_list(this);
}

void ReentPreParser::Prolog_inside_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_inside_list(this);
}

ReentPreParser::Prolog_inside_listContext* ReentPreParser::prolog_inside_list() {
  Prolog_inside_listContext *_localctx = _tracker.createInstance<Prolog_inside_listContext>(_ctx, getState());
  enterRule(_localctx, 150, ReentPreParser::RuleProlog_inside_list);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1279);
    prolog_parameter();
    setState(1282);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Comma) {
      setState(1280);
      match(ReentPreParser::Comma);
      setState(1281);
      prolog_inside_list();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_predicateContext ------------------------------------------------------------------

ReentPreParser::Prolog_predicateContext::Prolog_predicateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_predicateContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

ReentPreParser::Prolog_predicatesContext* ReentPreParser::Prolog_predicateContext::prolog_predicates() {
  return getRuleContext<ReentPreParser::Prolog_predicatesContext>(0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicateContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Prolog_predicateContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Prolog_predicateContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

tree::TerminalNode* ReentPreParser::Prolog_predicateContext::Not() {
  return getToken(ReentPreParser::Not, 0);
}

ReentPreParser::Prolog_callContext* ReentPreParser::Prolog_predicateContext::prolog_call() {
  return getRuleContext<ReentPreParser::Prolog_callContext>(0);
}

ReentPreParser::Is_expressionContext* ReentPreParser::Prolog_predicateContext::is_expression() {
  return getRuleContext<ReentPreParser::Is_expressionContext>(0);
}


size_t ReentPreParser::Prolog_predicateContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_predicate;
}

void ReentPreParser::Prolog_predicateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_predicate(this);
}

void ReentPreParser::Prolog_predicateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_predicate(this);
}

ReentPreParser::Prolog_predicateContext* ReentPreParser::prolog_predicate() {
  Prolog_predicateContext *_localctx = _tracker.createInstance<Prolog_predicateContext>(_ctx, getState());
  enterRule(_localctx, 152, ReentPreParser::RuleProlog_predicate);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(1308);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 187, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1284);
      match(ReentPreParser::LeftParen);
      setState(1288);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 184, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(1285);
          match(ReentPreParser::Newline); 
        }
        setState(1290);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 184, _ctx);
      }
      setState(1291);
      prolog_predicates();
      setState(1295);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Newline) {
        setState(1292);
        match(ReentPreParser::Newline);
        setState(1297);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(1298);
      match(ReentPreParser::RightParen);
      setState(1302);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 186, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(1299);
          match(ReentPreParser::Newline); 
        }
        setState(1304);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 186, _ctx);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1305);
      match(ReentPreParser::Not);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1306);
      prolog_call();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(1307);
      is_expression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_if_thenContext ------------------------------------------------------------------

ReentPreParser::Prolog_if_thenContext::Prolog_if_thenContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_if_thenContext::Arrow() {
  return getToken(ReentPreParser::Arrow, 0);
}

ReentPreParser::Prolog_predicateContext* ReentPreParser::Prolog_if_thenContext::prolog_predicate() {
  return getRuleContext<ReentPreParser::Prolog_predicateContext>(0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Prolog_if_thenContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Prolog_if_thenContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

tree::TerminalNode* ReentPreParser::Prolog_if_thenContext::Prolog_not() {
  return getToken(ReentPreParser::Prolog_not, 0);
}


size_t ReentPreParser::Prolog_if_thenContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_if_then;
}

void ReentPreParser::Prolog_if_thenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_if_then(this);
}

void ReentPreParser::Prolog_if_thenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_if_then(this);
}

ReentPreParser::Prolog_if_thenContext* ReentPreParser::prolog_if_then() {
  Prolog_if_thenContext *_localctx = _tracker.createInstance<Prolog_if_thenContext>(_ctx, getState());
  enterRule(_localctx, 154, ReentPreParser::RuleProlog_if_then);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1310);
    match(ReentPreParser::Arrow);
    setState(1314);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(1311);
      match(ReentPreParser::Newline);
      setState(1316);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1318);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Prolog_not) {
      setState(1317);
      match(ReentPreParser::Prolog_not);
    }
    setState(1320);
    prolog_predicate();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Is_expressionContext ------------------------------------------------------------------

ReentPreParser::Is_expressionContext::Is_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ReentPreParser::Relational_expressionContext *> ReentPreParser::Is_expressionContext::relational_expression() {
  return getRuleContexts<ReentPreParser::Relational_expressionContext>();
}

ReentPreParser::Relational_expressionContext* ReentPreParser::Is_expressionContext::relational_expression(size_t i) {
  return getRuleContext<ReentPreParser::Relational_expressionContext>(i);
}

tree::TerminalNode* ReentPreParser::Is_expressionContext::Is_() {
  return getToken(ReentPreParser::Is_, 0);
}


size_t ReentPreParser::Is_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleIs_expression;
}

void ReentPreParser::Is_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIs_expression(this);
}

void ReentPreParser::Is_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIs_expression(this);
}

ReentPreParser::Is_expressionContext* ReentPreParser::is_expression() {
  Is_expressionContext *_localctx = _tracker.createInstance<Is_expressionContext>(_ctx, getState());
  enterRule(_localctx, 156, ReentPreParser::RuleIs_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1322);
    relational_expression();
    setState(1325);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Is_) {
      setState(1323);
      match(ReentPreParser::Is_);
      setState(1324);
      relational_expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Relational_expressionContext ------------------------------------------------------------------

ReentPreParser::Relational_expressionContext::Relational_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::Pow_expressionContext* ReentPreParser::Relational_expressionContext::pow_expression() {
  return getRuleContext<ReentPreParser::Pow_expressionContext>(0);
}

ReentPreParser::Prolog_relationContext* ReentPreParser::Relational_expressionContext::prolog_relation() {
  return getRuleContext<ReentPreParser::Prolog_relationContext>(0);
}

ReentPreParser::Relational_expressionContext* ReentPreParser::Relational_expressionContext::relational_expression() {
  return getRuleContext<ReentPreParser::Relational_expressionContext>(0);
}


size_t ReentPreParser::Relational_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleRelational_expression;
}

void ReentPreParser::Relational_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelational_expression(this);
}

void ReentPreParser::Relational_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelational_expression(this);
}

ReentPreParser::Relational_expressionContext* ReentPreParser::relational_expression() {
  Relational_expressionContext *_localctx = _tracker.createInstance<Relational_expressionContext>(_ctx, getState());
  enterRule(_localctx, 158, ReentPreParser::RuleRelational_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1327);
    pow_expression();
    setState(1331);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 84) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 84)) & ((1ULL << (ReentPreParser::Less - 84))
      | (1ULL << (ReentPreParser::Greater - 84))
      | (1ULL << (ReentPreParser::Equal - 84))
      | (1ULL << (ReentPreParser::NotEqual - 84))
      | (1ULL << (ReentPreParser::LessEqual - 84))
      | (1ULL << (ReentPreParser::GreaterEqual - 84)))) != 0)) {
      setState(1328);
      prolog_relation();
      setState(1329);
      relational_expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_relationContext ------------------------------------------------------------------

ReentPreParser::Prolog_relationContext::Prolog_relationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_relationContext::Equal() {
  return getToken(ReentPreParser::Equal, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_relationContext::NotEqual() {
  return getToken(ReentPreParser::NotEqual, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_relationContext::Less() {
  return getToken(ReentPreParser::Less, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_relationContext::Greater() {
  return getToken(ReentPreParser::Greater, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_relationContext::LessEqual() {
  return getToken(ReentPreParser::LessEqual, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_relationContext::GreaterEqual() {
  return getToken(ReentPreParser::GreaterEqual, 0);
}


size_t ReentPreParser::Prolog_relationContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_relation;
}

void ReentPreParser::Prolog_relationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_relation(this);
}

void ReentPreParser::Prolog_relationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_relation(this);
}

ReentPreParser::Prolog_relationContext* ReentPreParser::prolog_relation() {
  Prolog_relationContext *_localctx = _tracker.createInstance<Prolog_relationContext>(_ctx, getState());
  enterRule(_localctx, 160, ReentPreParser::RuleProlog_relation);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1333);
    _la = _input->LA(1);
    if (!(((((_la - 84) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 84)) & ((1ULL << (ReentPreParser::Less - 84))
      | (1ULL << (ReentPreParser::Greater - 84))
      | (1ULL << (ReentPreParser::Equal - 84))
      | (1ULL << (ReentPreParser::NotEqual - 84))
      | (1ULL << (ReentPreParser::LessEqual - 84))
      | (1ULL << (ReentPreParser::GreaterEqual - 84)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Pow_expressionContext ------------------------------------------------------------------

ReentPreParser::Pow_expressionContext::Pow_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::Mul_div_expressionContext* ReentPreParser::Pow_expressionContext::mul_div_expression() {
  return getRuleContext<ReentPreParser::Mul_div_expressionContext>(0);
}

ReentPreParser::Prolog_powContext* ReentPreParser::Pow_expressionContext::prolog_pow() {
  return getRuleContext<ReentPreParser::Prolog_powContext>(0);
}

ReentPreParser::Pow_expressionContext* ReentPreParser::Pow_expressionContext::pow_expression() {
  return getRuleContext<ReentPreParser::Pow_expressionContext>(0);
}


size_t ReentPreParser::Pow_expressionContext::getRuleIndex() const {
  return ReentPreParser::RulePow_expression;
}

void ReentPreParser::Pow_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPow_expression(this);
}

void ReentPreParser::Pow_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPow_expression(this);
}

ReentPreParser::Pow_expressionContext* ReentPreParser::pow_expression() {
  Pow_expressionContext *_localctx = _tracker.createInstance<Pow_expressionContext>(_ctx, getState());
  enterRule(_localctx, 162, ReentPreParser::RulePow_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1335);
    mul_div_expression();
    setState(1339);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Star

    || _la == ReentPreParser::Caret) {
      setState(1336);
      prolog_pow();
      setState(1337);
      pow_expression();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_powContext ------------------------------------------------------------------

ReentPreParser::Prolog_powContext::Prolog_powContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ReentPreParser::Prolog_powContext::Star() {
  return getTokens(ReentPreParser::Star);
}

tree::TerminalNode* ReentPreParser::Prolog_powContext::Star(size_t i) {
  return getToken(ReentPreParser::Star, i);
}

tree::TerminalNode* ReentPreParser::Prolog_powContext::Caret() {
  return getToken(ReentPreParser::Caret, 0);
}


size_t ReentPreParser::Prolog_powContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_pow;
}

void ReentPreParser::Prolog_powContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_pow(this);
}

void ReentPreParser::Prolog_powContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_pow(this);
}

ReentPreParser::Prolog_powContext* ReentPreParser::prolog_pow() {
  Prolog_powContext *_localctx = _tracker.createInstance<Prolog_powContext>(_ctx, getState());
  enterRule(_localctx, 164, ReentPreParser::RuleProlog_pow);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1344);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Star: {
        enterOuterAlt(_localctx, 1);
        setState(1341);
        match(ReentPreParser::Star);
        setState(1342);
        match(ReentPreParser::Star);
        break;
      }

      case ReentPreParser::Caret: {
        enterOuterAlt(_localctx, 2);
        setState(1343);
        match(ReentPreParser::Caret);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Mul_div_expressionContext ------------------------------------------------------------------

ReentPreParser::Mul_div_expressionContext::Mul_div_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::Plus_min_expressionContext* ReentPreParser::Mul_div_expressionContext::plus_min_expression() {
  return getRuleContext<ReentPreParser::Plus_min_expressionContext>(0);
}

ReentPreParser::Prolog_mul_divContext* ReentPreParser::Mul_div_expressionContext::prolog_mul_div() {
  return getRuleContext<ReentPreParser::Prolog_mul_divContext>(0);
}

ReentPreParser::Mul_div_expressionContext* ReentPreParser::Mul_div_expressionContext::mul_div_expression() {
  return getRuleContext<ReentPreParser::Mul_div_expressionContext>(0);
}


size_t ReentPreParser::Mul_div_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleMul_div_expression;
}

void ReentPreParser::Mul_div_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMul_div_expression(this);
}

void ReentPreParser::Mul_div_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMul_div_expression(this);
}

ReentPreParser::Mul_div_expressionContext* ReentPreParser::mul_div_expression() {
  Mul_div_expressionContext *_localctx = _tracker.createInstance<Mul_div_expressionContext>(_ctx, getState());
  enterRule(_localctx, 166, ReentPreParser::RuleMul_div_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1346);
    plus_min_expression();
    setState(1350);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 194, _ctx)) {
    case 1: {
      setState(1347);
      prolog_mul_div();
      setState(1348);
      mul_div_expression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_mul_divContext ------------------------------------------------------------------

ReentPreParser::Prolog_mul_divContext::Prolog_mul_divContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_mul_divContext::Star() {
  return getToken(ReentPreParser::Star, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_mul_divContext::Rem() {
  return getToken(ReentPreParser::Rem, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_mul_divContext::Div_() {
  return getToken(ReentPreParser::Div_, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_mul_divContext::Mod_() {
  return getToken(ReentPreParser::Mod_, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Prolog_mul_divContext::Div() {
  return getTokens(ReentPreParser::Div);
}

tree::TerminalNode* ReentPreParser::Prolog_mul_divContext::Div(size_t i) {
  return getToken(ReentPreParser::Div, i);
}


size_t ReentPreParser::Prolog_mul_divContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_mul_div;
}

void ReentPreParser::Prolog_mul_divContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_mul_div(this);
}

void ReentPreParser::Prolog_mul_divContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_mul_div(this);
}

ReentPreParser::Prolog_mul_divContext* ReentPreParser::prolog_mul_div() {
  Prolog_mul_divContext *_localctx = _tracker.createInstance<Prolog_mul_divContext>(_ctx, getState());
  enterRule(_localctx, 168, ReentPreParser::RuleProlog_mul_div);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1360);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Star: {
        enterOuterAlt(_localctx, 1);
        setState(1352);
        match(ReentPreParser::Star);
        break;
      }

      case ReentPreParser::Rem: {
        enterOuterAlt(_localctx, 2);
        setState(1353);
        match(ReentPreParser::Rem);
        break;
      }

      case ReentPreParser::Div_: {
        enterOuterAlt(_localctx, 3);
        setState(1354);
        match(ReentPreParser::Div_);
        break;
      }

      case ReentPreParser::Mod_: {
        enterOuterAlt(_localctx, 4);
        setState(1355);
        match(ReentPreParser::Mod_);
        break;
      }

      case ReentPreParser::Div: {
        enterOuterAlt(_localctx, 5);
        setState(1356);
        match(ReentPreParser::Div);
        setState(1358);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Div) {
          setState(1357);
          match(ReentPreParser::Div);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Plus_min_expressionContext ------------------------------------------------------------------

ReentPreParser::Plus_min_expressionContext::Plus_min_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::Unary_expressionContext* ReentPreParser::Plus_min_expressionContext::unary_expression() {
  return getRuleContext<ReentPreParser::Unary_expressionContext>(0);
}

std::vector<ReentPreParser::Prolog_plus_minusContext *> ReentPreParser::Plus_min_expressionContext::prolog_plus_minus() {
  return getRuleContexts<ReentPreParser::Prolog_plus_minusContext>();
}

ReentPreParser::Prolog_plus_minusContext* ReentPreParser::Plus_min_expressionContext::prolog_plus_minus(size_t i) {
  return getRuleContext<ReentPreParser::Prolog_plus_minusContext>(i);
}

std::vector<ReentPreParser::Plus_min_expressionContext *> ReentPreParser::Plus_min_expressionContext::plus_min_expression() {
  return getRuleContexts<ReentPreParser::Plus_min_expressionContext>();
}

ReentPreParser::Plus_min_expressionContext* ReentPreParser::Plus_min_expressionContext::plus_min_expression(size_t i) {
  return getRuleContext<ReentPreParser::Plus_min_expressionContext>(i);
}


size_t ReentPreParser::Plus_min_expressionContext::getRuleIndex() const {
  return ReentPreParser::RulePlus_min_expression;
}

void ReentPreParser::Plus_min_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPlus_min_expression(this);
}

void ReentPreParser::Plus_min_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPlus_min_expression(this);
}

ReentPreParser::Plus_min_expressionContext* ReentPreParser::plus_min_expression() {
  Plus_min_expressionContext *_localctx = _tracker.createInstance<Plus_min_expressionContext>(_ctx, getState());
  enterRule(_localctx, 170, ReentPreParser::RulePlus_min_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1362);
    unary_expression();
    setState(1368);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 197, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1363);
        prolog_plus_minus();
        setState(1364);
        plus_min_expression(); 
      }
      setState(1370);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 197, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_plus_minusContext ------------------------------------------------------------------

ReentPreParser::Prolog_plus_minusContext::Prolog_plus_minusContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_plus_minusContext::Plus() {
  return getToken(ReentPreParser::Plus, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_plus_minusContext::Minus() {
  return getToken(ReentPreParser::Minus, 0);
}


size_t ReentPreParser::Prolog_plus_minusContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_plus_minus;
}

void ReentPreParser::Prolog_plus_minusContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_plus_minus(this);
}

void ReentPreParser::Prolog_plus_minusContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_plus_minus(this);
}

ReentPreParser::Prolog_plus_minusContext* ReentPreParser::prolog_plus_minus() {
  Prolog_plus_minusContext *_localctx = _tracker.createInstance<Prolog_plus_minusContext>(_ctx, getState());
  enterRule(_localctx, 172, ReentPreParser::RuleProlog_plus_minus);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1371);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::Plus

    || _la == ReentPreParser::Minus)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Unary_expressionContext ------------------------------------------------------------------

ReentPreParser::Unary_expressionContext::Unary_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::OperandContext* ReentPreParser::Unary_expressionContext::operand() {
  return getRuleContext<ReentPreParser::OperandContext>(0);
}

ReentPreParser::Prolog_plus_minusContext* ReentPreParser::Unary_expressionContext::prolog_plus_minus() {
  return getRuleContext<ReentPreParser::Prolog_plus_minusContext>(0);
}


size_t ReentPreParser::Unary_expressionContext::getRuleIndex() const {
  return ReentPreParser::RuleUnary_expression;
}

void ReentPreParser::Unary_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnary_expression(this);
}

void ReentPreParser::Unary_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnary_expression(this);
}

ReentPreParser::Unary_expressionContext* ReentPreParser::unary_expression() {
  Unary_expressionContext *_localctx = _tracker.createInstance<Unary_expressionContext>(_ctx, getState());
  enterRule(_localctx, 174, ReentPreParser::RuleUnary_expression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1374);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Plus

    || _la == ReentPreParser::Minus) {
      setState(1373);
      prolog_plus_minus();
    }
    setState(1376);
    operand();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperandContext ------------------------------------------------------------------

ReentPreParser::OperandContext::OperandContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::OperandContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

ReentPreParser::Relational_expressionContext* ReentPreParser::OperandContext::relational_expression() {
  return getRuleContext<ReentPreParser::Relational_expressionContext>(0);
}

tree::TerminalNode* ReentPreParser::OperandContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

ReentPreParser::OperandListContext* ReentPreParser::OperandContext::operandList() {
  return getRuleContext<ReentPreParser::OperandListContext>(0);
}

ReentPreParser::Prolog_termContext* ReentPreParser::OperandContext::prolog_term() {
  return getRuleContext<ReentPreParser::Prolog_termContext>(0);
}

tree::TerminalNode* ReentPreParser::OperandContext::EmptyAtom() {
  return getToken(ReentPreParser::EmptyAtom, 0);
}

ReentPreParser::LiteralContext* ReentPreParser::OperandContext::literal() {
  return getRuleContext<ReentPreParser::LiteralContext>(0);
}


size_t ReentPreParser::OperandContext::getRuleIndex() const {
  return ReentPreParser::RuleOperand;
}

void ReentPreParser::OperandContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperand(this);
}

void ReentPreParser::OperandContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperand(this);
}

ReentPreParser::OperandContext* ReentPreParser::operand() {
  OperandContext *_localctx = _tracker.createInstance<OperandContext>(_ctx, getState());
  enterRule(_localctx, 176, ReentPreParser::RuleOperand);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1386);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::LeftParen: {
        enterOuterAlt(_localctx, 1);
        setState(1378);
        match(ReentPreParser::LeftParen);
        setState(1379);
        relational_expression();
        setState(1380);
        match(ReentPreParser::RightParen);
        break;
      }

      case ReentPreParser::LeftBracket: {
        enterOuterAlt(_localctx, 2);
        setState(1382);
        operandList();
        break;
      }

      case ReentPreParser::Identifier: {
        enterOuterAlt(_localctx, 3);
        setState(1383);
        prolog_term();
        break;
      }

      case ReentPreParser::EmptyAtom: {
        enterOuterAlt(_localctx, 4);
        setState(1384);
        match(ReentPreParser::EmptyAtom);
        break;
      }

      case ReentPreParser::IntegerLiteral:
      case ReentPreParser::CharacterLiteral:
      case ReentPreParser::FloatingLiteral:
      case ReentPreParser::StringLiteral:
      case ReentPreParser::BooleanLiteral:
      case ReentPreParser::PointerLiteral:
      case ReentPreParser::UserDefinedLiteral: {
        enterOuterAlt(_localctx, 5);
        setState(1385);
        literal();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OperandListContext ------------------------------------------------------------------

ReentPreParser::OperandListContext::OperandListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::OperandListContext::LeftBracket() {
  return getToken(ReentPreParser::LeftBracket, 0);
}

tree::TerminalNode* ReentPreParser::OperandListContext::RightBracket() {
  return getToken(ReentPreParser::RightBracket, 0);
}

std::vector<ReentPreParser::Relational_expressionContext *> ReentPreParser::OperandListContext::relational_expression() {
  return getRuleContexts<ReentPreParser::Relational_expressionContext>();
}

ReentPreParser::Relational_expressionContext* ReentPreParser::OperandListContext::relational_expression(size_t i) {
  return getRuleContext<ReentPreParser::Relational_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::OperandListContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::OperandListContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}

tree::TerminalNode* ReentPreParser::OperandListContext::Or() {
  return getToken(ReentPreParser::Or, 0);
}


size_t ReentPreParser::OperandListContext::getRuleIndex() const {
  return ReentPreParser::RuleOperandList;
}

void ReentPreParser::OperandListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOperandList(this);
}

void ReentPreParser::OperandListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOperandList(this);
}

ReentPreParser::OperandListContext* ReentPreParser::operandList() {
  OperandListContext *_localctx = _tracker.createInstance<OperandListContext>(_ctx, getState());
  enterRule(_localctx, 178, ReentPreParser::RuleOperandList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1388);
    match(ReentPreParser::LeftBracket);
    setState(1401);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ReentPreParser::IntegerLiteral)
      | (1ULL << ReentPreParser::CharacterLiteral)
      | (1ULL << ReentPreParser::FloatingLiteral)
      | (1ULL << ReentPreParser::StringLiteral)
      | (1ULL << ReentPreParser::EmptyAtom)
      | (1ULL << ReentPreParser::BooleanLiteral)
      | (1ULL << ReentPreParser::PointerLiteral)
      | (1ULL << ReentPreParser::UserDefinedLiteral)
      | (1ULL << ReentPreParser::LeftParen)
      | (1ULL << ReentPreParser::LeftBracket))) != 0) || ((((_la - 73) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 73)) & ((1ULL << (ReentPreParser::Plus - 73))
      | (1ULL << (ReentPreParser::Minus - 73))
      | (1ULL << (ReentPreParser::Identifier - 73)))) != 0)) {
      setState(1389);
      relational_expression();
      setState(1394);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Comma) {
        setState(1390);
        match(ReentPreParser::Comma);
        setState(1391);
        relational_expression();
        setState(1396);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(1399);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Or) {
        setState(1397);
        match(ReentPreParser::Or);
        setState(1398);
        relational_expression();
      }
    }
    setState(1403);
    match(ReentPreParser::RightBracket);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_termContext ------------------------------------------------------------------

ReentPreParser::Prolog_termContext::Prolog_termContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_termContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_termContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_termContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

std::vector<ReentPreParser::Relational_expressionContext *> ReentPreParser::Prolog_termContext::relational_expression() {
  return getRuleContexts<ReentPreParser::Relational_expressionContext>();
}

ReentPreParser::Relational_expressionContext* ReentPreParser::Prolog_termContext::relational_expression(size_t i) {
  return getRuleContext<ReentPreParser::Relational_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Prolog_termContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Prolog_termContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::Prolog_termContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_term;
}

void ReentPreParser::Prolog_termContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_term(this);
}

void ReentPreParser::Prolog_termContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_term(this);
}

ReentPreParser::Prolog_termContext* ReentPreParser::prolog_term() {
  Prolog_termContext *_localctx = _tracker.createInstance<Prolog_termContext>(_ctx, getState());
  enterRule(_localctx, 180, ReentPreParser::RuleProlog_term);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1405);
    match(ReentPreParser::Identifier);
    setState(1418);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftParen) {
      setState(1406);
      match(ReentPreParser::LeftParen);
      setState(1415);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << ReentPreParser::IntegerLiteral)
        | (1ULL << ReentPreParser::CharacterLiteral)
        | (1ULL << ReentPreParser::FloatingLiteral)
        | (1ULL << ReentPreParser::StringLiteral)
        | (1ULL << ReentPreParser::EmptyAtom)
        | (1ULL << ReentPreParser::BooleanLiteral)
        | (1ULL << ReentPreParser::PointerLiteral)
        | (1ULL << ReentPreParser::UserDefinedLiteral)
        | (1ULL << ReentPreParser::LeftParen)
        | (1ULL << ReentPreParser::LeftBracket))) != 0) || ((((_la - 73) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 73)) & ((1ULL << (ReentPreParser::Plus - 73))
        | (1ULL << (ReentPreParser::Minus - 73))
        | (1ULL << (ReentPreParser::Identifier - 73)))) != 0)) {
        setState(1407);
        relational_expression();
        setState(1412);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ReentPreParser::Comma) {
          setState(1408);
          match(ReentPreParser::Comma);
          setState(1409);
          relational_expression();
          setState(1414);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(1417);
      match(ReentPreParser::RightParen);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_callContext ------------------------------------------------------------------

ReentPreParser::Prolog_callContext::Prolog_callContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ReentPreParser::Prolog_predicate_idContext* ReentPreParser::Prolog_callContext::prolog_predicate_id() {
  return getRuleContext<ReentPreParser::Prolog_predicate_idContext>(0);
}

ReentPreParser::Prolog_call_paramsContext* ReentPreParser::Prolog_callContext::prolog_call_params() {
  return getRuleContext<ReentPreParser::Prolog_call_paramsContext>(0);
}

tree::TerminalNode* ReentPreParser::Prolog_callContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}


size_t ReentPreParser::Prolog_callContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_call;
}

void ReentPreParser::Prolog_callContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_call(this);
}

void ReentPreParser::Prolog_callContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_call(this);
}

ReentPreParser::Prolog_callContext* ReentPreParser::prolog_call() {
  Prolog_callContext *_localctx = _tracker.createInstance<Prolog_callContext>(_ctx, getState());
  enterRule(_localctx, 182, ReentPreParser::RuleProlog_call);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1427);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Prolog_not_equal:
      case ReentPreParser::ConstructAtom:
      case ReentPreParser::Assign:
      case ReentPreParser::Less:
      case ReentPreParser::Greater:
      case ReentPreParser::Equal:
      case ReentPreParser::NotEqual:
      case ReentPreParser::LessEqual:
      case ReentPreParser::GreaterEqual:
      case ReentPreParser::Arrow:
      case ReentPreParser::Semi: {
        enterOuterAlt(_localctx, 1);
        setState(1420);
        prolog_predicate_id();
        setState(1421);
        prolog_call_params();
        break;
      }

      case ReentPreParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(1423);
        match(ReentPreParser::Identifier);
        setState(1425);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::LeftParen) {
          setState(1424);
          prolog_call_params();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_call_paramsContext ------------------------------------------------------------------

ReentPreParser::Prolog_call_paramsContext::Prolog_call_paramsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_call_paramsContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

std::vector<ReentPreParser::Prolog_parameterContext *> ReentPreParser::Prolog_call_paramsContext::prolog_parameter() {
  return getRuleContexts<ReentPreParser::Prolog_parameterContext>();
}

ReentPreParser::Prolog_parameterContext* ReentPreParser::Prolog_call_paramsContext::prolog_parameter(size_t i) {
  return getRuleContext<ReentPreParser::Prolog_parameterContext>(i);
}

tree::TerminalNode* ReentPreParser::Prolog_call_paramsContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::Prolog_call_paramsContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::Prolog_call_paramsContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Prolog_call_paramsContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::Prolog_call_paramsContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::Prolog_call_paramsContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_call_params;
}

void ReentPreParser::Prolog_call_paramsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_call_params(this);
}

void ReentPreParser::Prolog_call_paramsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_call_params(this);
}

ReentPreParser::Prolog_call_paramsContext* ReentPreParser::prolog_call_params() {
  Prolog_call_paramsContext *_localctx = _tracker.createInstance<Prolog_call_paramsContext>(_ctx, getState());
  enterRule(_localctx, 184, ReentPreParser::RuleProlog_call_params);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1429);
    match(ReentPreParser::LeftParen);
    setState(1433);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(1430);
      match(ReentPreParser::Newline);
      setState(1435);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1436);
    prolog_parameter();
    setState(1447);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(1437);
      match(ReentPreParser::Comma);
      setState(1441);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Newline) {
        setState(1438);
        match(ReentPreParser::Newline);
        setState(1443);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(1444);
      prolog_parameter();
      setState(1449);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1453);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(1450);
      match(ReentPreParser::Newline);
      setState(1455);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1456);
    match(ReentPreParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Prolog_predicate_idContext ------------------------------------------------------------------

ReentPreParser::Prolog_predicate_idContext::Prolog_predicate_idContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::Prolog_predicate_idContext::Semi() {
  return getToken(ReentPreParser::Semi, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicate_idContext::Less() {
  return getToken(ReentPreParser::Less, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicate_idContext::Assign() {
  return getToken(ReentPreParser::Assign, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicate_idContext::Greater() {
  return getToken(ReentPreParser::Greater, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicate_idContext::LessEqual() {
  return getToken(ReentPreParser::LessEqual, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicate_idContext::GreaterEqual() {
  return getToken(ReentPreParser::GreaterEqual, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicate_idContext::Equal() {
  return getToken(ReentPreParser::Equal, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicate_idContext::NotEqual() {
  return getToken(ReentPreParser::NotEqual, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicate_idContext::Arrow() {
  return getToken(ReentPreParser::Arrow, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicate_idContext::Prolog_not_equal() {
  return getToken(ReentPreParser::Prolog_not_equal, 0);
}

tree::TerminalNode* ReentPreParser::Prolog_predicate_idContext::ConstructAtom() {
  return getToken(ReentPreParser::ConstructAtom, 0);
}


size_t ReentPreParser::Prolog_predicate_idContext::getRuleIndex() const {
  return ReentPreParser::RuleProlog_predicate_id;
}

void ReentPreParser::Prolog_predicate_idContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProlog_predicate_id(this);
}

void ReentPreParser::Prolog_predicate_idContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProlog_predicate_id(this);
}

ReentPreParser::Prolog_predicate_idContext* ReentPreParser::prolog_predicate_id() {
  Prolog_predicate_idContext *_localctx = _tracker.createInstance<Prolog_predicate_idContext>(_ctx, getState());
  enterRule(_localctx, 186, ReentPreParser::RuleProlog_predicate_id);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1458);
    _la = _input->LA(1);
    if (!(((((_la - 68) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 68)) & ((1ULL << (ReentPreParser::Prolog_not_equal - 68))
      | (1ULL << (ReentPreParser::ConstructAtom - 68))
      | (1ULL << (ReentPreParser::Assign - 68))
      | (1ULL << (ReentPreParser::Less - 68))
      | (1ULL << (ReentPreParser::Greater - 68))
      | (1ULL << (ReentPreParser::Equal - 68))
      | (1ULL << (ReentPreParser::NotEqual - 68))
      | (1ULL << (ReentPreParser::LessEqual - 68))
      | (1ULL << (ReentPreParser::GreaterEqual - 68))
      | (1ULL << (ReentPreParser::Arrow - 68))
      | (1ULL << (ReentPreParser::Semi - 68)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Cpp_code_without_atContext ------------------------------------------------------------------

ReentPreParser::Cpp_code_without_atContext::Cpp_code_without_atContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ReentPreParser::Cpp_code_without_atContext::At() {
  return getTokens(ReentPreParser::At);
}

tree::TerminalNode* ReentPreParser::Cpp_code_without_atContext::At(size_t i) {
  return getToken(ReentPreParser::At, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Cpp_code_without_atContext::RightBrace() {
  return getTokens(ReentPreParser::RightBrace);
}

tree::TerminalNode* ReentPreParser::Cpp_code_without_atContext::RightBrace(size_t i) {
  return getToken(ReentPreParser::RightBrace, i);
}


size_t ReentPreParser::Cpp_code_without_atContext::getRuleIndex() const {
  return ReentPreParser::RuleCpp_code_without_at;
}

void ReentPreParser::Cpp_code_without_atContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCpp_code_without_at(this);
}

void ReentPreParser::Cpp_code_without_atContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCpp_code_without_at(this);
}

ReentPreParser::Cpp_code_without_atContext* ReentPreParser::cpp_code_without_at() {
  Cpp_code_without_atContext *_localctx = _tracker.createInstance<Cpp_code_without_atContext>(_ctx, getState());
  enterRule(_localctx, 188, ReentPreParser::RuleCpp_code_without_at);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1461); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(1460);
              _la = _input->LA(1);
              if (_la == 0 || _la == Token::EOF || (_la == ReentPreParser::RightBrace

              || _la == ReentPreParser::At)) {
              _errHandler->recoverInline(this);
              }
              else {
                _errHandler->reportMatch(this);
                consume();
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(1463); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 212, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjCilkSpawnArgContext ------------------------------------------------------------------

ReentPreParser::ObjCilkSpawnArgContext::ObjCilkSpawnArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnArgContext::Assign() {
  return getToken(ReentPreParser::Assign, 0);
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnArgContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

ReentPreParser::Cpp_balanced_expressionContext* ReentPreParser::ObjCilkSpawnArgContext::cpp_balanced_expression() {
  return getRuleContext<ReentPreParser::Cpp_balanced_expressionContext>(0);
}


size_t ReentPreParser::ObjCilkSpawnArgContext::getRuleIndex() const {
  return ReentPreParser::RuleObjCilkSpawnArg;
}

void ReentPreParser::ObjCilkSpawnArgContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjCilkSpawnArg(this);
}

void ReentPreParser::ObjCilkSpawnArgContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjCilkSpawnArg(this);
}

ReentPreParser::ObjCilkSpawnArgContext* ReentPreParser::objCilkSpawnArg() {
  ObjCilkSpawnArgContext *_localctx = _tracker.createInstance<ObjCilkSpawnArgContext>(_ctx, getState());
  enterRule(_localctx, 190, ReentPreParser::RuleObjCilkSpawnArg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1468);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 213, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1465);
      match(ReentPreParser::Assign);
      setState(1466);
      match(ReentPreParser::Identifier);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1467);
      cpp_balanced_expression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjCilkSpawnParamsContext ------------------------------------------------------------------

ReentPreParser::ObjCilkSpawnParamsContext::ObjCilkSpawnParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnParamsContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

std::vector<ReentPreParser::Cpp_balanced_expressionContext *> ReentPreParser::ObjCilkSpawnParamsContext::cpp_balanced_expression() {
  return getRuleContexts<ReentPreParser::Cpp_balanced_expressionContext>();
}

ReentPreParser::Cpp_balanced_expressionContext* ReentPreParser::ObjCilkSpawnParamsContext::cpp_balanced_expression(size_t i) {
  return getRuleContext<ReentPreParser::Cpp_balanced_expressionContext>(i);
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnParamsContext::Comma() {
  return getToken(ReentPreParser::Comma, 0);
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnParamsContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}


size_t ReentPreParser::ObjCilkSpawnParamsContext::getRuleIndex() const {
  return ReentPreParser::RuleObjCilkSpawnParams;
}

void ReentPreParser::ObjCilkSpawnParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjCilkSpawnParams(this);
}

void ReentPreParser::ObjCilkSpawnParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjCilkSpawnParams(this);
}

ReentPreParser::ObjCilkSpawnParamsContext* ReentPreParser::objCilkSpawnParams() {
  ObjCilkSpawnParamsContext *_localctx = _tracker.createInstance<ObjCilkSpawnParamsContext>(_ctx, getState());
  enterRule(_localctx, 192, ReentPreParser::RuleObjCilkSpawnParams);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1470);
    match(ReentPreParser::LeftParen);
    setState(1471);
    cpp_balanced_expression();
    setState(1472);
    match(ReentPreParser::Comma);
    setState(1473);
    cpp_balanced_expression();
    setState(1474);
    match(ReentPreParser::RightParen);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjCilkDesignatorContext ------------------------------------------------------------------

ReentPreParser::ObjCilkDesignatorContext::ObjCilkDesignatorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::ObjCilkDesignatorContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::ObjCilkDesignatorContext::Dot() {
  return getToken(ReentPreParser::Dot, 0);
}

tree::TerminalNode* ReentPreParser::ObjCilkDesignatorContext::Arrow() {
  return getToken(ReentPreParser::Arrow, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::ObjCilkDesignatorContext::LeftBracket() {
  return getTokens(ReentPreParser::LeftBracket);
}

tree::TerminalNode* ReentPreParser::ObjCilkDesignatorContext::LeftBracket(size_t i) {
  return getToken(ReentPreParser::LeftBracket, i);
}

std::vector<ReentPreParser::Cpp_balanced_expressionContext *> ReentPreParser::ObjCilkDesignatorContext::cpp_balanced_expression() {
  return getRuleContexts<ReentPreParser::Cpp_balanced_expressionContext>();
}

ReentPreParser::Cpp_balanced_expressionContext* ReentPreParser::ObjCilkDesignatorContext::cpp_balanced_expression(size_t i) {
  return getRuleContext<ReentPreParser::Cpp_balanced_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::ObjCilkDesignatorContext::RightBracket() {
  return getTokens(ReentPreParser::RightBracket);
}

tree::TerminalNode* ReentPreParser::ObjCilkDesignatorContext::RightBracket(size_t i) {
  return getToken(ReentPreParser::RightBracket, i);
}


size_t ReentPreParser::ObjCilkDesignatorContext::getRuleIndex() const {
  return ReentPreParser::RuleObjCilkDesignator;
}

void ReentPreParser::ObjCilkDesignatorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjCilkDesignator(this);
}

void ReentPreParser::ObjCilkDesignatorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjCilkDesignator(this);
}

ReentPreParser::ObjCilkDesignatorContext* ReentPreParser::objCilkDesignator() {
  ObjCilkDesignatorContext *_localctx = _tracker.createInstance<ObjCilkDesignatorContext>(_ctx, getState());
  enterRule(_localctx, 194, ReentPreParser::RuleObjCilkDesignator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1476);
    match(ReentPreParser::Identifier);
    setState(1483);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::LeftBracket) {
      setState(1477);
      match(ReentPreParser::LeftBracket);
      setState(1478);
      cpp_balanced_expression();
      setState(1479);
      match(ReentPreParser::RightBracket);
      setState(1485);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1486);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::Arrow

    || _la == ReentPreParser::Dot)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjCilkAssignContext ------------------------------------------------------------------

ReentPreParser::ObjCilkAssignContext::ObjCilkAssignContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::ObjCilkAssignContext::Assign() {
  return getToken(ReentPreParser::Assign, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::ObjCilkAssignContext::Identifier() {
  return getTokens(ReentPreParser::Identifier);
}

tree::TerminalNode* ReentPreParser::ObjCilkAssignContext::Identifier(size_t i) {
  return getToken(ReentPreParser::Identifier, i);
}

std::vector<tree::TerminalNode *> ReentPreParser::ObjCilkAssignContext::LeftBracket() {
  return getTokens(ReentPreParser::LeftBracket);
}

tree::TerminalNode* ReentPreParser::ObjCilkAssignContext::LeftBracket(size_t i) {
  return getToken(ReentPreParser::LeftBracket, i);
}

std::vector<ReentPreParser::Cpp_balanced_expressionContext *> ReentPreParser::ObjCilkAssignContext::cpp_balanced_expression() {
  return getRuleContexts<ReentPreParser::Cpp_balanced_expressionContext>();
}

ReentPreParser::Cpp_balanced_expressionContext* ReentPreParser::ObjCilkAssignContext::cpp_balanced_expression(size_t i) {
  return getRuleContext<ReentPreParser::Cpp_balanced_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::ObjCilkAssignContext::RightBracket() {
  return getTokens(ReentPreParser::RightBracket);
}

tree::TerminalNode* ReentPreParser::ObjCilkAssignContext::RightBracket(size_t i) {
  return getToken(ReentPreParser::RightBracket, i);
}


size_t ReentPreParser::ObjCilkAssignContext::getRuleIndex() const {
  return ReentPreParser::RuleObjCilkAssign;
}

void ReentPreParser::ObjCilkAssignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjCilkAssign(this);
}

void ReentPreParser::ObjCilkAssignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjCilkAssign(this);
}

ReentPreParser::ObjCilkAssignContext* ReentPreParser::objCilkAssign() {
  ObjCilkAssignContext *_localctx = _tracker.createInstance<ObjCilkAssignContext>(_ctx, getState());
  enterRule(_localctx, 196, ReentPreParser::RuleObjCilkAssign);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1489); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(1488);
      match(ReentPreParser::Identifier);
      setState(1491); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ReentPreParser::Identifier);
    setState(1499);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::LeftBracket) {
      setState(1493);
      match(ReentPreParser::LeftBracket);
      setState(1494);
      cpp_balanced_expression();
      setState(1495);
      match(ReentPreParser::RightBracket);
      setState(1501);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1502);
    match(ReentPreParser::Assign);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjCilkSpawnContext ------------------------------------------------------------------

ReentPreParser::ObjCilkSpawnContext::ObjCilkSpawnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnContext::Cilk_spawn() {
  return getToken(ReentPreParser::Cilk_spawn, 0);
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnContext::Identifier() {
  return getToken(ReentPreParser::Identifier, 0);
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnContext::Semi() {
  return getToken(ReentPreParser::Semi, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::ObjCilkSpawnContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

ReentPreParser::ObjCilkAssignContext* ReentPreParser::ObjCilkSpawnContext::objCilkAssign() {
  return getRuleContext<ReentPreParser::ObjCilkAssignContext>(0);
}

std::vector<ReentPreParser::ObjCilkDesignatorContext *> ReentPreParser::ObjCilkSpawnContext::objCilkDesignator() {
  return getRuleContexts<ReentPreParser::ObjCilkDesignatorContext>();
}

ReentPreParser::ObjCilkDesignatorContext* ReentPreParser::ObjCilkSpawnContext::objCilkDesignator(size_t i) {
  return getRuleContext<ReentPreParser::ObjCilkDesignatorContext>(i);
}

ReentPreParser::ObjCilkSpawnParamsContext* ReentPreParser::ObjCilkSpawnContext::objCilkSpawnParams() {
  return getRuleContext<ReentPreParser::ObjCilkSpawnParamsContext>(0);
}

std::vector<ReentPreParser::ObjCilkSpawnArgContext *> ReentPreParser::ObjCilkSpawnContext::objCilkSpawnArg() {
  return getRuleContexts<ReentPreParser::ObjCilkSpawnArgContext>();
}

ReentPreParser::ObjCilkSpawnArgContext* ReentPreParser::ObjCilkSpawnContext::objCilkSpawnArg(size_t i) {
  return getRuleContext<ReentPreParser::ObjCilkSpawnArgContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::ObjCilkSpawnContext::Comma() {
  return getTokens(ReentPreParser::Comma);
}

tree::TerminalNode* ReentPreParser::ObjCilkSpawnContext::Comma(size_t i) {
  return getToken(ReentPreParser::Comma, i);
}


size_t ReentPreParser::ObjCilkSpawnContext::getRuleIndex() const {
  return ReentPreParser::RuleObjCilkSpawn;
}

void ReentPreParser::ObjCilkSpawnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjCilkSpawn(this);
}

void ReentPreParser::ObjCilkSpawnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjCilkSpawn(this);
}

ReentPreParser::ObjCilkSpawnContext* ReentPreParser::objCilkSpawn() {
  ObjCilkSpawnContext *_localctx = _tracker.createInstance<ObjCilkSpawnContext>(_ctx, getState());
  enterRule(_localctx, 198, ReentPreParser::RuleObjCilkSpawn);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1505);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 217, _ctx)) {
    case 1: {
      setState(1504);
      objCilkAssign();
      break;
    }

    default:
      break;
    }
    setState(1510);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 218, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(1507);
        objCilkDesignator(); 
      }
      setState(1512);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 218, _ctx);
    }
    setState(1513);
    match(ReentPreParser::Cilk_spawn);

    setState(1515);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftParen) {
      setState(1514);
      objCilkSpawnParams();
    }
    setState(1520);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 220, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(1517);
        objCilkDesignator(); 
      }
      setState(1522);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 220, _ctx);
    }
    setState(1523);
    match(ReentPreParser::Identifier);
    setState(1524);
    match(ReentPreParser::LeftParen);
    setState(1533);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ReentPreParser::Regexp_fragment)
      | (1ULL << ReentPreParser::Regexp_set)
      | (1ULL << ReentPreParser::IntegerLiteral)
      | (1ULL << ReentPreParser::CharacterLiteral)
      | (1ULL << ReentPreParser::FloatingLiteral)
      | (1ULL << ReentPreParser::StringLiteral)
      | (1ULL << ReentPreParser::EmptyAtom)
      | (1ULL << ReentPreParser::BooleanLiteral)
      | (1ULL << ReentPreParser::PointerLiteral)
      | (1ULL << ReentPreParser::UserDefinedLiteral)
      | (1ULL << ReentPreParser::DefModule)
      | (1ULL << ReentPreParser::DefMemoization)
      | (1ULL << ReentPreParser::DoNotCheck)
      | (1ULL << ReentPreParser::DefOtherPragma)
      | (1ULL << ReentPreParser::Introduce)
      | (1ULL << ReentPreParser::MetaSentence)
      | (1ULL << ReentPreParser::Stop)
      | (1ULL << ReentPreParser::PreprocPasses)
      | (1ULL << ReentPreParser::AddScan)
      | (1ULL << ReentPreParser::Scan)
      | (1ULL << ReentPreParser::AddParse)
      | (1ULL << ReentPreParser::Parse)
      | (1ULL << ReentPreParser::DefPattern)
      | (1ULL << ReentPreParser::DefXPath)
      | (1ULL << ReentPreParser::Line)
      | (1ULL << ReentPreParser::MultiLineMacro)
      | (1ULL << ReentPreParser::Directive)
      | (1ULL << ReentPreParser::AtValue)
      | (1ULL << ReentPreParser::Cilk_spawn)
      | (1ULL << ReentPreParser::Cilk_sync)
      | (1ULL << ReentPreParser::Conditions)
      | (1ULL << ReentPreParser::Controlled)
      | (1ULL << ReentPreParser::Div_)
      | (1ULL << ReentPreParser::False_)
      | (1ULL << ReentPreParser::Feed_forward)
      | (1ULL << ReentPreParser::GetText)
      | (1ULL << ReentPreParser::Goal)
      | (1ULL << ReentPreParser::Lin_extrapolator)
      | (1ULL << ReentPreParser::Mgua)
      | (1ULL << ReentPreParser::Mod_)
      | (1ULL << ReentPreParser::Nullptr)
      | (1ULL << ReentPreParser::Regexp_analyze)
      | (1ULL << ReentPreParser::Regexp_begin)
      | (1ULL << ReentPreParser::Regexp_end)
      | (1ULL << ReentPreParser::Regexp_parallel)
      | (1ULL << ReentPreParser::Regexp_sequential)
      | (1ULL << ReentPreParser::Rem)
      | (1ULL << ReentPreParser::True_)
      | (1ULL << ReentPreParser::Plc_regexp_var)
      | (1ULL << ReentPreParser::Plc_regexp_equal)
      | (1ULL << ReentPreParser::Plc_regexp_not_equal)
      | (1ULL << ReentPreParser::Plc_regexp_query)
      | (1ULL << ReentPreParser::LeftParen)
      | (1ULL << ReentPreParser::LeftBracket)
      | (1ULL << ReentPreParser::LeftBrace)
      | (1ULL << ReentPreParser::RightBrace)
      | (1ULL << ReentPreParser::AssignGreater)
      | (1ULL << ReentPreParser::DivDiv)
      | (1ULL << ReentPreParser::Pound)
      | (1ULL << ReentPreParser::And_)
      | (1ULL << ReentPreParser::Or_))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (ReentPreParser::At - 64))
      | (1ULL << (ReentPreParser::Is - 64))
      | (1ULL << (ReentPreParser::Is_ - 64))
      | (1ULL << (ReentPreParser::Prolog_not - 64))
      | (1ULL << (ReentPreParser::Prolog_not_equal - 64))
      | (1ULL << (ReentPreParser::Slash - 64))
      | (1ULL << (ReentPreParser::ConstructAtom - 64))
      | (1ULL << (ReentPreParser::Regexp_ref - 64))
      | (1ULL << (ReentPreParser::Underscore - 64))
      | (1ULL << (ReentPreParser::Plus - 64))
      | (1ULL << (ReentPreParser::Minus - 64))
      | (1ULL << (ReentPreParser::Star - 64))
      | (1ULL << (ReentPreParser::Div - 64))
      | (1ULL << (ReentPreParser::Mod - 64))
      | (1ULL << (ReentPreParser::Caret - 64))
      | (1ULL << (ReentPreParser::And - 64))
      | (1ULL << (ReentPreParser::Or - 64))
      | (1ULL << (ReentPreParser::Tilde - 64))
      | (1ULL << (ReentPreParser::Not - 64))
      | (1ULL << (ReentPreParser::Assign - 64))
      | (1ULL << (ReentPreParser::Less - 64))
      | (1ULL << (ReentPreParser::Greater - 64))
      | (1ULL << (ReentPreParser::Equal - 64))
      | (1ULL << (ReentPreParser::NotEqual - 64))
      | (1ULL << (ReentPreParser::LessEqual - 64))
      | (1ULL << (ReentPreParser::GreaterEqual - 64))
      | (1ULL << (ReentPreParser::AndAnd - 64))
      | (1ULL << (ReentPreParser::OrOr - 64))
      | (1ULL << (ReentPreParser::Arrow - 64))
      | (1ULL << (ReentPreParser::Question - 64))
      | (1ULL << (ReentPreParser::Colon - 64))
      | (1ULL << (ReentPreParser::Doublecolon - 64))
      | (1ULL << (ReentPreParser::Semi - 64))
      | (1ULL << (ReentPreParser::Dot - 64))
      | (1ULL << (ReentPreParser::DotStar - 64))
      | (1ULL << (ReentPreParser::Ellipsis - 64))
      | (1ULL << (ReentPreParser::Identifier - 64))
      | (1ULL << (ReentPreParser::DecimalLiteral - 64))
      | (1ULL << (ReentPreParser::OctalLiteral - 64))
      | (1ULL << (ReentPreParser::HexadecimalLiteral - 64))
      | (1ULL << (ReentPreParser::BinaryLiteral - 64))
      | (1ULL << (ReentPreParser::Integersuffix - 64))
      | (1ULL << (ReentPreParser::UserDefinedIntegerLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedFloatingLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedStringLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedCharacterLiteral - 64))
      | (1ULL << (ReentPreParser::Whitespace - 64))
      | (1ULL << (ReentPreParser::Newline - 64))
      | (1ULL << (ReentPreParser::BlockComment - 64))
      | (1ULL << (ReentPreParser::LineComment - 64))
      | (1ULL << (ReentPreParser::PrologComment - 64)))) != 0)) {
      setState(1525);
      objCilkSpawnArg();
      setState(1530);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Comma) {
        setState(1526);
        match(ReentPreParser::Comma);
        setState(1527);
        objCilkSpawnArg();
        setState(1532);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(1535);
    match(ReentPreParser::RightParen);
    setState(1536);
    match(ReentPreParser::Semi);
    setState(1540);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ReentPreParser::Regexp_fragment)
      | (1ULL << ReentPreParser::Regexp_set)
      | (1ULL << ReentPreParser::IntegerLiteral)
      | (1ULL << ReentPreParser::CharacterLiteral)
      | (1ULL << ReentPreParser::FloatingLiteral)
      | (1ULL << ReentPreParser::StringLiteral)
      | (1ULL << ReentPreParser::EmptyAtom)
      | (1ULL << ReentPreParser::BooleanLiteral)
      | (1ULL << ReentPreParser::PointerLiteral)
      | (1ULL << ReentPreParser::UserDefinedLiteral)
      | (1ULL << ReentPreParser::DefModule)
      | (1ULL << ReentPreParser::DefMemoization)
      | (1ULL << ReentPreParser::DoNotCheck)
      | (1ULL << ReentPreParser::DefOtherPragma)
      | (1ULL << ReentPreParser::Introduce)
      | (1ULL << ReentPreParser::MetaSentence)
      | (1ULL << ReentPreParser::Stop)
      | (1ULL << ReentPreParser::PreprocPasses)
      | (1ULL << ReentPreParser::AddScan)
      | (1ULL << ReentPreParser::Scan)
      | (1ULL << ReentPreParser::AddParse)
      | (1ULL << ReentPreParser::Parse)
      | (1ULL << ReentPreParser::DefPattern)
      | (1ULL << ReentPreParser::DefXPath)
      | (1ULL << ReentPreParser::Line)
      | (1ULL << ReentPreParser::MultiLineMacro)
      | (1ULL << ReentPreParser::Directive)
      | (1ULL << ReentPreParser::AtValue)
      | (1ULL << ReentPreParser::Cilk_spawn)
      | (1ULL << ReentPreParser::Cilk_sync)
      | (1ULL << ReentPreParser::Conditions)
      | (1ULL << ReentPreParser::Controlled)
      | (1ULL << ReentPreParser::Div_)
      | (1ULL << ReentPreParser::False_)
      | (1ULL << ReentPreParser::Feed_forward)
      | (1ULL << ReentPreParser::GetText)
      | (1ULL << ReentPreParser::Goal)
      | (1ULL << ReentPreParser::Lin_extrapolator)
      | (1ULL << ReentPreParser::Mgua)
      | (1ULL << ReentPreParser::Mod_)
      | (1ULL << ReentPreParser::Nullptr)
      | (1ULL << ReentPreParser::Regexp_analyze)
      | (1ULL << ReentPreParser::Regexp_begin)
      | (1ULL << ReentPreParser::Regexp_end)
      | (1ULL << ReentPreParser::Regexp_parallel)
      | (1ULL << ReentPreParser::Regexp_sequential)
      | (1ULL << ReentPreParser::Rem)
      | (1ULL << ReentPreParser::True_)
      | (1ULL << ReentPreParser::Plc_regexp_var)
      | (1ULL << ReentPreParser::Plc_regexp_equal)
      | (1ULL << ReentPreParser::Plc_regexp_not_equal)
      | (1ULL << ReentPreParser::Plc_regexp_query)
      | (1ULL << ReentPreParser::LeftParen)
      | (1ULL << ReentPreParser::RightParen)
      | (1ULL << ReentPreParser::LeftBracket)
      | (1ULL << ReentPreParser::RightBracket)
      | (1ULL << ReentPreParser::LeftBrace)
      | (1ULL << ReentPreParser::RightBrace)
      | (1ULL << ReentPreParser::AssignGreater)
      | (1ULL << ReentPreParser::DivDiv)
      | (1ULL << ReentPreParser::Pound)
      | (1ULL << ReentPreParser::And_)
      | (1ULL << ReentPreParser::Or_))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (ReentPreParser::At - 64))
      | (1ULL << (ReentPreParser::Is - 64))
      | (1ULL << (ReentPreParser::Is_ - 64))
      | (1ULL << (ReentPreParser::Prolog_not - 64))
      | (1ULL << (ReentPreParser::Prolog_not_equal - 64))
      | (1ULL << (ReentPreParser::Slash - 64))
      | (1ULL << (ReentPreParser::ConstructAtom - 64))
      | (1ULL << (ReentPreParser::Regexp_ref - 64))
      | (1ULL << (ReentPreParser::Underscore - 64))
      | (1ULL << (ReentPreParser::Plus - 64))
      | (1ULL << (ReentPreParser::Minus - 64))
      | (1ULL << (ReentPreParser::Star - 64))
      | (1ULL << (ReentPreParser::Div - 64))
      | (1ULL << (ReentPreParser::Mod - 64))
      | (1ULL << (ReentPreParser::Caret - 64))
      | (1ULL << (ReentPreParser::And - 64))
      | (1ULL << (ReentPreParser::Or - 64))
      | (1ULL << (ReentPreParser::Tilde - 64))
      | (1ULL << (ReentPreParser::Not - 64))
      | (1ULL << (ReentPreParser::Assign - 64))
      | (1ULL << (ReentPreParser::Less - 64))
      | (1ULL << (ReentPreParser::Greater - 64))
      | (1ULL << (ReentPreParser::Equal - 64))
      | (1ULL << (ReentPreParser::NotEqual - 64))
      | (1ULL << (ReentPreParser::LessEqual - 64))
      | (1ULL << (ReentPreParser::GreaterEqual - 64))
      | (1ULL << (ReentPreParser::AndAnd - 64))
      | (1ULL << (ReentPreParser::OrOr - 64))
      | (1ULL << (ReentPreParser::Comma - 64))
      | (1ULL << (ReentPreParser::Arrow - 64))
      | (1ULL << (ReentPreParser::Question - 64))
      | (1ULL << (ReentPreParser::Colon - 64))
      | (1ULL << (ReentPreParser::Doublecolon - 64))
      | (1ULL << (ReentPreParser::Semi - 64))
      | (1ULL << (ReentPreParser::Dot - 64))
      | (1ULL << (ReentPreParser::DotStar - 64))
      | (1ULL << (ReentPreParser::Ellipsis - 64))
      | (1ULL << (ReentPreParser::Identifier - 64))
      | (1ULL << (ReentPreParser::DecimalLiteral - 64))
      | (1ULL << (ReentPreParser::OctalLiteral - 64))
      | (1ULL << (ReentPreParser::HexadecimalLiteral - 64))
      | (1ULL << (ReentPreParser::BinaryLiteral - 64))
      | (1ULL << (ReentPreParser::Integersuffix - 64))
      | (1ULL << (ReentPreParser::UserDefinedIntegerLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedFloatingLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedStringLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedCharacterLiteral - 64))
      | (1ULL << (ReentPreParser::Whitespace - 64))
      | (1ULL << (ReentPreParser::BlockComment - 64))
      | (1ULL << (ReentPreParser::LineComment - 64))
      | (1ULL << (ReentPreParser::PrologComment - 64)))) != 0)) {
      setState(1537);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == ReentPreParser::Newline)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1542);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1543);
    match(ReentPreParser::Newline);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjCilkSyncContext ------------------------------------------------------------------

ReentPreParser::ObjCilkSyncContext::ObjCilkSyncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::ObjCilkSyncContext::Cilk_sync() {
  return getToken(ReentPreParser::Cilk_sync, 0);
}

tree::TerminalNode* ReentPreParser::ObjCilkSyncContext::Semi() {
  return getToken(ReentPreParser::Semi, 0);
}

std::vector<tree::TerminalNode *> ReentPreParser::ObjCilkSyncContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::ObjCilkSyncContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}

std::vector<ReentPreParser::ObjCilkDesignatorContext *> ReentPreParser::ObjCilkSyncContext::objCilkDesignator() {
  return getRuleContexts<ReentPreParser::ObjCilkDesignatorContext>();
}

ReentPreParser::ObjCilkDesignatorContext* ReentPreParser::ObjCilkSyncContext::objCilkDesignator(size_t i) {
  return getRuleContext<ReentPreParser::ObjCilkDesignatorContext>(i);
}

tree::TerminalNode* ReentPreParser::ObjCilkSyncContext::LeftParen() {
  return getToken(ReentPreParser::LeftParen, 0);
}

tree::TerminalNode* ReentPreParser::ObjCilkSyncContext::RightParen() {
  return getToken(ReentPreParser::RightParen, 0);
}

ReentPreParser::Cpp_balanced_expressionContext* ReentPreParser::ObjCilkSyncContext::cpp_balanced_expression() {
  return getRuleContext<ReentPreParser::Cpp_balanced_expressionContext>(0);
}


size_t ReentPreParser::ObjCilkSyncContext::getRuleIndex() const {
  return ReentPreParser::RuleObjCilkSync;
}

void ReentPreParser::ObjCilkSyncContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterObjCilkSync(this);
}

void ReentPreParser::ObjCilkSyncContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitObjCilkSync(this);
}

ReentPreParser::ObjCilkSyncContext* ReentPreParser::objCilkSync() {
  ObjCilkSyncContext *_localctx = _tracker.createInstance<ObjCilkSyncContext>(_ctx, getState());
  enterRule(_localctx, 200, ReentPreParser::RuleObjCilkSync);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1548);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 224, _ctx);
    while (alt != 1 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1 + 1) {
        setState(1545);
        objCilkDesignator(); 
      }
      setState(1550);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 224, _ctx);
    }
    setState(1551);
    match(ReentPreParser::Cilk_sync);

    setState(1557);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftParen) {
      setState(1552);
      match(ReentPreParser::LeftParen);
      setState(1554);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << ReentPreParser::Regexp_fragment)
        | (1ULL << ReentPreParser::Regexp_set)
        | (1ULL << ReentPreParser::IntegerLiteral)
        | (1ULL << ReentPreParser::CharacterLiteral)
        | (1ULL << ReentPreParser::FloatingLiteral)
        | (1ULL << ReentPreParser::StringLiteral)
        | (1ULL << ReentPreParser::EmptyAtom)
        | (1ULL << ReentPreParser::BooleanLiteral)
        | (1ULL << ReentPreParser::PointerLiteral)
        | (1ULL << ReentPreParser::UserDefinedLiteral)
        | (1ULL << ReentPreParser::DefModule)
        | (1ULL << ReentPreParser::DefMemoization)
        | (1ULL << ReentPreParser::DoNotCheck)
        | (1ULL << ReentPreParser::DefOtherPragma)
        | (1ULL << ReentPreParser::Introduce)
        | (1ULL << ReentPreParser::MetaSentence)
        | (1ULL << ReentPreParser::Stop)
        | (1ULL << ReentPreParser::PreprocPasses)
        | (1ULL << ReentPreParser::AddScan)
        | (1ULL << ReentPreParser::Scan)
        | (1ULL << ReentPreParser::AddParse)
        | (1ULL << ReentPreParser::Parse)
        | (1ULL << ReentPreParser::DefPattern)
        | (1ULL << ReentPreParser::DefXPath)
        | (1ULL << ReentPreParser::Line)
        | (1ULL << ReentPreParser::MultiLineMacro)
        | (1ULL << ReentPreParser::Directive)
        | (1ULL << ReentPreParser::AtValue)
        | (1ULL << ReentPreParser::Cilk_spawn)
        | (1ULL << ReentPreParser::Cilk_sync)
        | (1ULL << ReentPreParser::Conditions)
        | (1ULL << ReentPreParser::Controlled)
        | (1ULL << ReentPreParser::Div_)
        | (1ULL << ReentPreParser::False_)
        | (1ULL << ReentPreParser::Feed_forward)
        | (1ULL << ReentPreParser::GetText)
        | (1ULL << ReentPreParser::Goal)
        | (1ULL << ReentPreParser::Lin_extrapolator)
        | (1ULL << ReentPreParser::Mgua)
        | (1ULL << ReentPreParser::Mod_)
        | (1ULL << ReentPreParser::Nullptr)
        | (1ULL << ReentPreParser::Regexp_analyze)
        | (1ULL << ReentPreParser::Regexp_begin)
        | (1ULL << ReentPreParser::Regexp_end)
        | (1ULL << ReentPreParser::Regexp_parallel)
        | (1ULL << ReentPreParser::Regexp_sequential)
        | (1ULL << ReentPreParser::Rem)
        | (1ULL << ReentPreParser::True_)
        | (1ULL << ReentPreParser::Plc_regexp_var)
        | (1ULL << ReentPreParser::Plc_regexp_equal)
        | (1ULL << ReentPreParser::Plc_regexp_not_equal)
        | (1ULL << ReentPreParser::Plc_regexp_query)
        | (1ULL << ReentPreParser::LeftParen)
        | (1ULL << ReentPreParser::LeftBracket)
        | (1ULL << ReentPreParser::LeftBrace)
        | (1ULL << ReentPreParser::RightBrace)
        | (1ULL << ReentPreParser::AssignGreater)
        | (1ULL << ReentPreParser::DivDiv)
        | (1ULL << ReentPreParser::Pound)
        | (1ULL << ReentPreParser::And_)
        | (1ULL << ReentPreParser::Or_))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 64)) & ((1ULL << (ReentPreParser::At - 64))
        | (1ULL << (ReentPreParser::Is - 64))
        | (1ULL << (ReentPreParser::Is_ - 64))
        | (1ULL << (ReentPreParser::Prolog_not - 64))
        | (1ULL << (ReentPreParser::Prolog_not_equal - 64))
        | (1ULL << (ReentPreParser::Slash - 64))
        | (1ULL << (ReentPreParser::ConstructAtom - 64))
        | (1ULL << (ReentPreParser::Regexp_ref - 64))
        | (1ULL << (ReentPreParser::Underscore - 64))
        | (1ULL << (ReentPreParser::Plus - 64))
        | (1ULL << (ReentPreParser::Minus - 64))
        | (1ULL << (ReentPreParser::Star - 64))
        | (1ULL << (ReentPreParser::Div - 64))
        | (1ULL << (ReentPreParser::Mod - 64))
        | (1ULL << (ReentPreParser::Caret - 64))
        | (1ULL << (ReentPreParser::And - 64))
        | (1ULL << (ReentPreParser::Or - 64))
        | (1ULL << (ReentPreParser::Tilde - 64))
        | (1ULL << (ReentPreParser::Not - 64))
        | (1ULL << (ReentPreParser::Assign - 64))
        | (1ULL << (ReentPreParser::Less - 64))
        | (1ULL << (ReentPreParser::Greater - 64))
        | (1ULL << (ReentPreParser::Equal - 64))
        | (1ULL << (ReentPreParser::NotEqual - 64))
        | (1ULL << (ReentPreParser::LessEqual - 64))
        | (1ULL << (ReentPreParser::GreaterEqual - 64))
        | (1ULL << (ReentPreParser::AndAnd - 64))
        | (1ULL << (ReentPreParser::OrOr - 64))
        | (1ULL << (ReentPreParser::Arrow - 64))
        | (1ULL << (ReentPreParser::Question - 64))
        | (1ULL << (ReentPreParser::Colon - 64))
        | (1ULL << (ReentPreParser::Doublecolon - 64))
        | (1ULL << (ReentPreParser::Semi - 64))
        | (1ULL << (ReentPreParser::Dot - 64))
        | (1ULL << (ReentPreParser::DotStar - 64))
        | (1ULL << (ReentPreParser::Ellipsis - 64))
        | (1ULL << (ReentPreParser::Identifier - 64))
        | (1ULL << (ReentPreParser::DecimalLiteral - 64))
        | (1ULL << (ReentPreParser::OctalLiteral - 64))
        | (1ULL << (ReentPreParser::HexadecimalLiteral - 64))
        | (1ULL << (ReentPreParser::BinaryLiteral - 64))
        | (1ULL << (ReentPreParser::Integersuffix - 64))
        | (1ULL << (ReentPreParser::UserDefinedIntegerLiteral - 64))
        | (1ULL << (ReentPreParser::UserDefinedFloatingLiteral - 64))
        | (1ULL << (ReentPreParser::UserDefinedStringLiteral - 64))
        | (1ULL << (ReentPreParser::UserDefinedCharacterLiteral - 64))
        | (1ULL << (ReentPreParser::Whitespace - 64))
        | (1ULL << (ReentPreParser::Newline - 64))
        | (1ULL << (ReentPreParser::BlockComment - 64))
        | (1ULL << (ReentPreParser::LineComment - 64))
        | (1ULL << (ReentPreParser::PrologComment - 64)))) != 0)) {
        setState(1553);
        cpp_balanced_expression();
      }
      setState(1556);
      match(ReentPreParser::RightParen);
    }
    setState(1559);
    match(ReentPreParser::Semi);
    setState(1563);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ReentPreParser::Regexp_fragment)
      | (1ULL << ReentPreParser::Regexp_set)
      | (1ULL << ReentPreParser::IntegerLiteral)
      | (1ULL << ReentPreParser::CharacterLiteral)
      | (1ULL << ReentPreParser::FloatingLiteral)
      | (1ULL << ReentPreParser::StringLiteral)
      | (1ULL << ReentPreParser::EmptyAtom)
      | (1ULL << ReentPreParser::BooleanLiteral)
      | (1ULL << ReentPreParser::PointerLiteral)
      | (1ULL << ReentPreParser::UserDefinedLiteral)
      | (1ULL << ReentPreParser::DefModule)
      | (1ULL << ReentPreParser::DefMemoization)
      | (1ULL << ReentPreParser::DoNotCheck)
      | (1ULL << ReentPreParser::DefOtherPragma)
      | (1ULL << ReentPreParser::Introduce)
      | (1ULL << ReentPreParser::MetaSentence)
      | (1ULL << ReentPreParser::Stop)
      | (1ULL << ReentPreParser::PreprocPasses)
      | (1ULL << ReentPreParser::AddScan)
      | (1ULL << ReentPreParser::Scan)
      | (1ULL << ReentPreParser::AddParse)
      | (1ULL << ReentPreParser::Parse)
      | (1ULL << ReentPreParser::DefPattern)
      | (1ULL << ReentPreParser::DefXPath)
      | (1ULL << ReentPreParser::Line)
      | (1ULL << ReentPreParser::MultiLineMacro)
      | (1ULL << ReentPreParser::Directive)
      | (1ULL << ReentPreParser::AtValue)
      | (1ULL << ReentPreParser::Cilk_spawn)
      | (1ULL << ReentPreParser::Cilk_sync)
      | (1ULL << ReentPreParser::Conditions)
      | (1ULL << ReentPreParser::Controlled)
      | (1ULL << ReentPreParser::Div_)
      | (1ULL << ReentPreParser::False_)
      | (1ULL << ReentPreParser::Feed_forward)
      | (1ULL << ReentPreParser::GetText)
      | (1ULL << ReentPreParser::Goal)
      | (1ULL << ReentPreParser::Lin_extrapolator)
      | (1ULL << ReentPreParser::Mgua)
      | (1ULL << ReentPreParser::Mod_)
      | (1ULL << ReentPreParser::Nullptr)
      | (1ULL << ReentPreParser::Regexp_analyze)
      | (1ULL << ReentPreParser::Regexp_begin)
      | (1ULL << ReentPreParser::Regexp_end)
      | (1ULL << ReentPreParser::Regexp_parallel)
      | (1ULL << ReentPreParser::Regexp_sequential)
      | (1ULL << ReentPreParser::Rem)
      | (1ULL << ReentPreParser::True_)
      | (1ULL << ReentPreParser::Plc_regexp_var)
      | (1ULL << ReentPreParser::Plc_regexp_equal)
      | (1ULL << ReentPreParser::Plc_regexp_not_equal)
      | (1ULL << ReentPreParser::Plc_regexp_query)
      | (1ULL << ReentPreParser::LeftParen)
      | (1ULL << ReentPreParser::RightParen)
      | (1ULL << ReentPreParser::LeftBracket)
      | (1ULL << ReentPreParser::RightBracket)
      | (1ULL << ReentPreParser::LeftBrace)
      | (1ULL << ReentPreParser::RightBrace)
      | (1ULL << ReentPreParser::AssignGreater)
      | (1ULL << ReentPreParser::DivDiv)
      | (1ULL << ReentPreParser::Pound)
      | (1ULL << ReentPreParser::And_)
      | (1ULL << ReentPreParser::Or_))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (ReentPreParser::At - 64))
      | (1ULL << (ReentPreParser::Is - 64))
      | (1ULL << (ReentPreParser::Is_ - 64))
      | (1ULL << (ReentPreParser::Prolog_not - 64))
      | (1ULL << (ReentPreParser::Prolog_not_equal - 64))
      | (1ULL << (ReentPreParser::Slash - 64))
      | (1ULL << (ReentPreParser::ConstructAtom - 64))
      | (1ULL << (ReentPreParser::Regexp_ref - 64))
      | (1ULL << (ReentPreParser::Underscore - 64))
      | (1ULL << (ReentPreParser::Plus - 64))
      | (1ULL << (ReentPreParser::Minus - 64))
      | (1ULL << (ReentPreParser::Star - 64))
      | (1ULL << (ReentPreParser::Div - 64))
      | (1ULL << (ReentPreParser::Mod - 64))
      | (1ULL << (ReentPreParser::Caret - 64))
      | (1ULL << (ReentPreParser::And - 64))
      | (1ULL << (ReentPreParser::Or - 64))
      | (1ULL << (ReentPreParser::Tilde - 64))
      | (1ULL << (ReentPreParser::Not - 64))
      | (1ULL << (ReentPreParser::Assign - 64))
      | (1ULL << (ReentPreParser::Less - 64))
      | (1ULL << (ReentPreParser::Greater - 64))
      | (1ULL << (ReentPreParser::Equal - 64))
      | (1ULL << (ReentPreParser::NotEqual - 64))
      | (1ULL << (ReentPreParser::LessEqual - 64))
      | (1ULL << (ReentPreParser::GreaterEqual - 64))
      | (1ULL << (ReentPreParser::AndAnd - 64))
      | (1ULL << (ReentPreParser::OrOr - 64))
      | (1ULL << (ReentPreParser::Comma - 64))
      | (1ULL << (ReentPreParser::Arrow - 64))
      | (1ULL << (ReentPreParser::Question - 64))
      | (1ULL << (ReentPreParser::Colon - 64))
      | (1ULL << (ReentPreParser::Doublecolon - 64))
      | (1ULL << (ReentPreParser::Semi - 64))
      | (1ULL << (ReentPreParser::Dot - 64))
      | (1ULL << (ReentPreParser::DotStar - 64))
      | (1ULL << (ReentPreParser::Ellipsis - 64))
      | (1ULL << (ReentPreParser::Identifier - 64))
      | (1ULL << (ReentPreParser::DecimalLiteral - 64))
      | (1ULL << (ReentPreParser::OctalLiteral - 64))
      | (1ULL << (ReentPreParser::HexadecimalLiteral - 64))
      | (1ULL << (ReentPreParser::BinaryLiteral - 64))
      | (1ULL << (ReentPreParser::Integersuffix - 64))
      | (1ULL << (ReentPreParser::UserDefinedIntegerLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedFloatingLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedStringLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedCharacterLiteral - 64))
      | (1ULL << (ReentPreParser::Whitespace - 64))
      | (1ULL << (ReentPreParser::BlockComment - 64))
      | (1ULL << (ReentPreParser::LineComment - 64))
      | (1ULL << (ReentPreParser::PrologComment - 64)))) != 0)) {
      setState(1560);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == ReentPreParser::Newline)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1565);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1566);
    match(ReentPreParser::Newline);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OtherLineContext ------------------------------------------------------------------

ReentPreParser::OtherLineContext::OtherLineContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ReentPreParser::OtherLineContext::Newline() {
  return getTokens(ReentPreParser::Newline);
}

tree::TerminalNode* ReentPreParser::OtherLineContext::Newline(size_t i) {
  return getToken(ReentPreParser::Newline, i);
}


size_t ReentPreParser::OtherLineContext::getRuleIndex() const {
  return ReentPreParser::RuleOtherLine;
}

void ReentPreParser::OtherLineContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOtherLine(this);
}

void ReentPreParser::OtherLineContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOtherLine(this);
}

ReentPreParser::OtherLineContext* ReentPreParser::otherLine() {
  OtherLineContext *_localctx = _tracker.createInstance<OtherLineContext>(_ctx, getState());
  enterRule(_localctx, 202, ReentPreParser::RuleOtherLine);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1568);

    if (!( _input->LT(-1) == NULL || _input->LT(-1)->getText() == "\n" )) throw FailedPredicateException(this, " _input->LT(-1) == NULL || _input->LT(-1)->getText() == \"\\n\" ");
    setState(1572);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ReentPreParser::Regexp_fragment)
      | (1ULL << ReentPreParser::Regexp_set)
      | (1ULL << ReentPreParser::IntegerLiteral)
      | (1ULL << ReentPreParser::CharacterLiteral)
      | (1ULL << ReentPreParser::FloatingLiteral)
      | (1ULL << ReentPreParser::StringLiteral)
      | (1ULL << ReentPreParser::EmptyAtom)
      | (1ULL << ReentPreParser::BooleanLiteral)
      | (1ULL << ReentPreParser::PointerLiteral)
      | (1ULL << ReentPreParser::UserDefinedLiteral)
      | (1ULL << ReentPreParser::DefModule)
      | (1ULL << ReentPreParser::DefMemoization)
      | (1ULL << ReentPreParser::DoNotCheck)
      | (1ULL << ReentPreParser::DefOtherPragma)
      | (1ULL << ReentPreParser::Introduce)
      | (1ULL << ReentPreParser::MetaSentence)
      | (1ULL << ReentPreParser::Stop)
      | (1ULL << ReentPreParser::PreprocPasses)
      | (1ULL << ReentPreParser::AddScan)
      | (1ULL << ReentPreParser::Scan)
      | (1ULL << ReentPreParser::AddParse)
      | (1ULL << ReentPreParser::Parse)
      | (1ULL << ReentPreParser::DefPattern)
      | (1ULL << ReentPreParser::DefXPath)
      | (1ULL << ReentPreParser::Line)
      | (1ULL << ReentPreParser::MultiLineMacro)
      | (1ULL << ReentPreParser::Directive)
      | (1ULL << ReentPreParser::AtValue)
      | (1ULL << ReentPreParser::Cilk_spawn)
      | (1ULL << ReentPreParser::Cilk_sync)
      | (1ULL << ReentPreParser::Conditions)
      | (1ULL << ReentPreParser::Controlled)
      | (1ULL << ReentPreParser::Div_)
      | (1ULL << ReentPreParser::False_)
      | (1ULL << ReentPreParser::Feed_forward)
      | (1ULL << ReentPreParser::GetText)
      | (1ULL << ReentPreParser::Goal)
      | (1ULL << ReentPreParser::Lin_extrapolator)
      | (1ULL << ReentPreParser::Mgua)
      | (1ULL << ReentPreParser::Mod_)
      | (1ULL << ReentPreParser::Nullptr)
      | (1ULL << ReentPreParser::Regexp_analyze)
      | (1ULL << ReentPreParser::Regexp_begin)
      | (1ULL << ReentPreParser::Regexp_end)
      | (1ULL << ReentPreParser::Regexp_parallel)
      | (1ULL << ReentPreParser::Regexp_sequential)
      | (1ULL << ReentPreParser::Rem)
      | (1ULL << ReentPreParser::True_)
      | (1ULL << ReentPreParser::Plc_regexp_var)
      | (1ULL << ReentPreParser::Plc_regexp_equal)
      | (1ULL << ReentPreParser::Plc_regexp_not_equal)
      | (1ULL << ReentPreParser::Plc_regexp_query)
      | (1ULL << ReentPreParser::LeftParen)
      | (1ULL << ReentPreParser::RightParen)
      | (1ULL << ReentPreParser::LeftBracket)
      | (1ULL << ReentPreParser::RightBracket)
      | (1ULL << ReentPreParser::LeftBrace)
      | (1ULL << ReentPreParser::RightBrace)
      | (1ULL << ReentPreParser::AssignGreater)
      | (1ULL << ReentPreParser::DivDiv)
      | (1ULL << ReentPreParser::Pound)
      | (1ULL << ReentPreParser::And_)
      | (1ULL << ReentPreParser::Or_))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (ReentPreParser::At - 64))
      | (1ULL << (ReentPreParser::Is - 64))
      | (1ULL << (ReentPreParser::Is_ - 64))
      | (1ULL << (ReentPreParser::Prolog_not - 64))
      | (1ULL << (ReentPreParser::Prolog_not_equal - 64))
      | (1ULL << (ReentPreParser::Slash - 64))
      | (1ULL << (ReentPreParser::ConstructAtom - 64))
      | (1ULL << (ReentPreParser::Regexp_ref - 64))
      | (1ULL << (ReentPreParser::Underscore - 64))
      | (1ULL << (ReentPreParser::Plus - 64))
      | (1ULL << (ReentPreParser::Minus - 64))
      | (1ULL << (ReentPreParser::Star - 64))
      | (1ULL << (ReentPreParser::Div - 64))
      | (1ULL << (ReentPreParser::Mod - 64))
      | (1ULL << (ReentPreParser::Caret - 64))
      | (1ULL << (ReentPreParser::And - 64))
      | (1ULL << (ReentPreParser::Or - 64))
      | (1ULL << (ReentPreParser::Tilde - 64))
      | (1ULL << (ReentPreParser::Not - 64))
      | (1ULL << (ReentPreParser::Assign - 64))
      | (1ULL << (ReentPreParser::Less - 64))
      | (1ULL << (ReentPreParser::Greater - 64))
      | (1ULL << (ReentPreParser::Equal - 64))
      | (1ULL << (ReentPreParser::NotEqual - 64))
      | (1ULL << (ReentPreParser::LessEqual - 64))
      | (1ULL << (ReentPreParser::GreaterEqual - 64))
      | (1ULL << (ReentPreParser::AndAnd - 64))
      | (1ULL << (ReentPreParser::OrOr - 64))
      | (1ULL << (ReentPreParser::Comma - 64))
      | (1ULL << (ReentPreParser::Arrow - 64))
      | (1ULL << (ReentPreParser::Question - 64))
      | (1ULL << (ReentPreParser::Colon - 64))
      | (1ULL << (ReentPreParser::Doublecolon - 64))
      | (1ULL << (ReentPreParser::Semi - 64))
      | (1ULL << (ReentPreParser::Dot - 64))
      | (1ULL << (ReentPreParser::DotStar - 64))
      | (1ULL << (ReentPreParser::Ellipsis - 64))
      | (1ULL << (ReentPreParser::Identifier - 64))
      | (1ULL << (ReentPreParser::DecimalLiteral - 64))
      | (1ULL << (ReentPreParser::OctalLiteral - 64))
      | (1ULL << (ReentPreParser::HexadecimalLiteral - 64))
      | (1ULL << (ReentPreParser::BinaryLiteral - 64))
      | (1ULL << (ReentPreParser::Integersuffix - 64))
      | (1ULL << (ReentPreParser::UserDefinedIntegerLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedFloatingLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedStringLiteral - 64))
      | (1ULL << (ReentPreParser::UserDefinedCharacterLiteral - 64))
      | (1ULL << (ReentPreParser::Whitespace - 64))
      | (1ULL << (ReentPreParser::BlockComment - 64))
      | (1ULL << (ReentPreParser::LineComment - 64))
      | (1ULL << (ReentPreParser::PrologComment - 64)))) != 0)) {
      setState(1569);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == ReentPreParser::Newline)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1574);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1575);
    match(ReentPreParser::Newline);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

ReentPreParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ReentPreParser::LiteralContext::IntegerLiteral() {
  return getToken(ReentPreParser::IntegerLiteral, 0);
}

tree::TerminalNode* ReentPreParser::LiteralContext::CharacterLiteral() {
  return getToken(ReentPreParser::CharacterLiteral, 0);
}

tree::TerminalNode* ReentPreParser::LiteralContext::FloatingLiteral() {
  return getToken(ReentPreParser::FloatingLiteral, 0);
}

tree::TerminalNode* ReentPreParser::LiteralContext::StringLiteral() {
  return getToken(ReentPreParser::StringLiteral, 0);
}

tree::TerminalNode* ReentPreParser::LiteralContext::BooleanLiteral() {
  return getToken(ReentPreParser::BooleanLiteral, 0);
}

tree::TerminalNode* ReentPreParser::LiteralContext::PointerLiteral() {
  return getToken(ReentPreParser::PointerLiteral, 0);
}

tree::TerminalNode* ReentPreParser::LiteralContext::UserDefinedLiteral() {
  return getToken(ReentPreParser::UserDefinedLiteral, 0);
}


size_t ReentPreParser::LiteralContext::getRuleIndex() const {
  return ReentPreParser::RuleLiteral;
}

void ReentPreParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void ReentPreParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ReentPreParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}

ReentPreParser::LiteralContext* ReentPreParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 204, ReentPreParser::RuleLiteral);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1577);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ReentPreParser::IntegerLiteral)
      | (1ULL << ReentPreParser::CharacterLiteral)
      | (1ULL << ReentPreParser::FloatingLiteral)
      | (1ULL << ReentPreParser::StringLiteral)
      | (1ULL << ReentPreParser::BooleanLiteral)
      | (1ULL << ReentPreParser::PointerLiteral)
      | (1ULL << ReentPreParser::UserDefinedLiteral))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool ReentPreParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 28: return regexp_bodySempred(dynamic_cast<Regexp_bodyContext *>(context), predicateIndex);
    case 51: return memoMapTypeSempred(dynamic_cast<MemoMapTypeContext *>(context), predicateIndex);
    case 58: return nnet_layer_typeSempred(dynamic_cast<Nnet_layer_typeContext *>(context), predicateIndex);
    case 101: return otherLineSempred(dynamic_cast<OtherLineContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ReentPreParser::regexp_bodySempred(Regexp_bodyContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return 
    		!_input->LT(-1) || _input->LT(-1)->getText()!="\n" ||
    		(_input->LT(1) && _input->LT(1)->getText() != "@begin" && _input->LT(1)->getText() != "@end" &&
    		 (_input->LT(1)->getText() != "}" || _input->LT(2) && _input->LT(2)->getText() != ";"))
    	;

  default:
    break;
  }
  return true;
}

bool ReentPreParser::memoMapTypeSempred(MemoMapTypeContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return  _input->LT(1)->getText() == "i" || _input->LT(1)->getText() == "o" ||
    	  _input->LT(1)->getText() == "g" || _input->LT(1)->getText() == "t" ;

  default:
    break;
  }
  return true;
}

bool ReentPreParser::nnet_layer_typeSempred(Nnet_layer_typeContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return  _input->LT(1)->getText() == "e" || _input->LT(1)->getText() == "l" ||
    	  _input->LT(1)->getText() == "h" || _input->LT(1)->getText() == "r" ;

  default:
    break;
  }
  return true;
}

bool ReentPreParser::otherLineSempred(OtherLineContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return  _input->LT(-1) == NULL || _input->LT(-1)->getText() == "\n" ;

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> ReentPreParser::_decisionToDFA;
atn::PredictionContextCache ReentPreParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ReentPreParser::_atn;
std::vector<uint16_t> ReentPreParser::_serializedATN;

std::vector<std::string> ReentPreParser::_ruleNames = {
  "translationUnit", "statementseq", "statement", "def_pattern", "put_fact", 
  "def_pattern_param", "simple_xpath_expression", "xpath_and_expression", 
  "xpath_rel_expression", "xpath_mul_expression", "xpath_plus_expression", 
  "xpath_unary_expression", "xpath_query", "xpath_predicate", "xpath_fun_params", 
  "def_xpath", "def_xpath_param", "def_xpath_expression", "def_xpath_and_expression", 
  "def_xpath_rel_expression", "def_xpath_mul_expression", "def_xpath_plus_expression", 
  "def_xpath_unary_expression", "def_xpath_query", "def_xpath_predicate", 
  "def_xpath_fun_params", "regexps", "regexp_lines", "regexp_body", "plc_regexp_logical", 
  "plc_regexp_var", "plc_regexp_equal", "plc_regexp_not_equal", "plc_regexp_query", 
  "regexp_or_sequence", "regexp_and_sequence", "regexp_unary", "regexp_pred", 
  "regexp_pred_arg", "regexp_pred_parallel", "defModule", "defModuleDescriptors", 
  "defModuleDescriptor", "defMemoization", "preprocPasses", "addScan", "scan", 
  "addParse", "parse", "scanners_list", "memoMapItem", "memoMapType", "cpp_balanced_expression", 
  "memoizationStyle", "mgua", "nnet", "extrapolator", "nnet_layer_specifier", 
  "nnet_layer_type", "controlPredicate", "automated_control", "by_conditions_control", 
  "blockHeader", "typeItem", "typeSpecifier", "templateParameters", "templateParameter", 
  "parameter", "dimension", "prolog_goal", "prolog_statement", "prolog_parameters", 
  "prolog_predicates", "prolog_parameter", "prolog_parameter_list", "prolog_inside_list", 
  "prolog_predicate", "prolog_if_then", "is_expression", "relational_expression", 
  "prolog_relation", "pow_expression", "prolog_pow", "mul_div_expression", 
  "prolog_mul_div", "plus_min_expression", "prolog_plus_minus", "unary_expression", 
  "operand", "operandList", "prolog_term", "prolog_call", "prolog_call_params", 
  "prolog_predicate_id", "cpp_code_without_at", "objCilkSpawnArg", "objCilkSpawnParams", 
  "objCilkDesignator", "objCilkAssign", "objCilkSpawn", "objCilkSync", "otherLine", 
  "literal"
};

std::vector<std::string> ReentPreParser::_literalNames = {
  "", "", "", "", "", "", "", "''''", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "'@Value'", "'cilk_spawn'", 
  "'cilk_sync'", "'conditions'", "'controlled'", "'div'", "'false'", "'feed_forward'", 
  "'text()'", "'goal'", "'lin_extrapolator'", "'mgua'", "'mod'", "'nullptr'", 
  "'analyze'", "'@begin'", "'@end'", "'parallel'", "'sequential'", "'rem'", 
  "'true'", "')->{'", "')==>{'", "')!=>{'", "')\u003F=>{'", "'('", "')'", 
  "'['", "']'", "'{'", "'}'", "'=>'", "'//'", "'#'", "'and'", "'or'", "'@'", 
  "':-'", "'is'", "'\\+'", "'\\='", "'\\'", "'=..'", "'$'", "'_'", "'+'", 
  "'-'", "'*'", "'/'", "'%'", "'^'", "'&'", "'|'", "'~'", "", "'='", "'<'", 
  "'>'", "'=='", "'!='", "'<='", "'>='", "", "", "','", "'->'", "'\u003F'", 
  "':'", "'::'", "';'", "'.'", "'.*'", "'...'"
};

std::vector<std::string> ReentPreParser::_symbolicNames = {
  "", "Regexp_fragment", "Regexp_set", "IntegerLiteral", "CharacterLiteral", 
  "FloatingLiteral", "StringLiteral", "EmptyAtom", "BooleanLiteral", "PointerLiteral", 
  "UserDefinedLiteral", "DefModule", "DefMemoization", "DoNotCheck", "DefOtherPragma", 
  "Introduce", "MetaSentence", "Stop", "PreprocPasses", "AddScan", "Scan", 
  "AddParse", "Parse", "DefPattern", "DefXPath", "Line", "MultiLineMacro", 
  "Directive", "AtValue", "Cilk_spawn", "Cilk_sync", "Conditions", "Controlled", 
  "Div_", "False_", "Feed_forward", "GetText", "Goal", "Lin_extrapolator", 
  "Mgua", "Mod_", "Nullptr", "Regexp_analyze", "Regexp_begin", "Regexp_end", 
  "Regexp_parallel", "Regexp_sequential", "Rem", "True_", "Plc_regexp_var", 
  "Plc_regexp_equal", "Plc_regexp_not_equal", "Plc_regexp_query", "LeftParen", 
  "RightParen", "LeftBracket", "RightBracket", "LeftBrace", "RightBrace", 
  "AssignGreater", "DivDiv", "Pound", "And_", "Or_", "At", "Is", "Is_", 
  "Prolog_not", "Prolog_not_equal", "Slash", "ConstructAtom", "Regexp_ref", 
  "Underscore", "Plus", "Minus", "Star", "Div", "Mod", "Caret", "And", "Or", 
  "Tilde", "Not", "Assign", "Less", "Greater", "Equal", "NotEqual", "LessEqual", 
  "GreaterEqual", "AndAnd", "OrOr", "Comma", "Arrow", "Question", "Colon", 
  "Doublecolon", "Semi", "Dot", "DotStar", "Ellipsis", "Identifier", "DecimalLiteral", 
  "OctalLiteral", "HexadecimalLiteral", "BinaryLiteral", "Integersuffix", 
  "UserDefinedIntegerLiteral", "UserDefinedFloatingLiteral", "UserDefinedStringLiteral", 
  "UserDefinedCharacterLiteral", "Whitespace", "Newline", "BlockComment", 
  "LineComment", "PrologComment"
};

dfa::Vocabulary ReentPreParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ReentPreParser::_tokenNames;

ReentPreParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  static const uint16_t serializedATNSegment0[] = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
       0x3, 0x75, 0x62e, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
       0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 
       0x7, 0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 
       0x4, 0xb, 0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 
       0xe, 0x9, 0xe, 0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 
       0x9, 0x11, 0x4, 0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 
       0x9, 0x14, 0x4, 0x15, 0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 
       0x9, 0x17, 0x4, 0x18, 0x9, 0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 
       0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 
       0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 0x1f, 0x9, 0x1f, 0x4, 0x20, 
       0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 0x9, 0x22, 0x4, 0x23, 
       0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 0x25, 0x4, 0x26, 
       0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 0x4, 0x29, 
       0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 0x2c, 
       0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
       0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 
       0x9, 0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 
       0x9, 0x35, 0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 
       0x9, 0x38, 0x4, 0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 
       0x9, 0x3b, 0x4, 0x3c, 0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 
       0x9, 0x3e, 0x4, 0x3f, 0x9, 0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 
       0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 
       0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 0x46, 0x9, 0x46, 0x4, 0x47, 
       0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 0x9, 0x49, 0x4, 0x4a, 
       0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 0x4c, 0x4, 0x4d, 
       0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f, 0x4, 0x50, 
       0x9, 0x50, 0x4, 0x51, 0x9, 0x51, 0x4, 0x52, 0x9, 0x52, 0x4, 0x53, 
       0x9, 0x53, 0x4, 0x54, 0x9, 0x54, 0x4, 0x55, 0x9, 0x55, 0x4, 0x56, 
       0x9, 0x56, 0x4, 0x57, 0x9, 0x57, 0x4, 0x58, 0x9, 0x58, 0x4, 0x59, 
       0x9, 0x59, 0x4, 0x5a, 0x9, 0x5a, 0x4, 0x5b, 0x9, 0x5b, 0x4, 0x5c, 
       0x9, 0x5c, 0x4, 0x5d, 0x9, 0x5d, 0x4, 0x5e, 0x9, 0x5e, 0x4, 0x5f, 
       0x9, 0x5f, 0x4, 0x60, 0x9, 0x60, 0x4, 0x61, 0x9, 0x61, 0x4, 0x62, 
       0x9, 0x62, 0x4, 0x63, 0x9, 0x63, 0x4, 0x64, 0x9, 0x64, 0x4, 0x65, 
       0x9, 0x65, 0x4, 0x66, 0x9, 0x66, 0x4, 0x67, 0x9, 0x67, 0x4, 0x68, 
       0x9, 0x68, 0x3, 0x2, 0x5, 0x2, 0xd2, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 
       0x3, 0x2, 0x3, 0x3, 0x6, 0x3, 0xd8, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 
       0xd9, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0xf9, 0xa, 0x4, 0x3, 
       0x4, 0x7, 0x4, 0xfc, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0xff, 0xb, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x7, 0x4, 0x105, 0xa, 0x4, 
       0xc, 0x4, 0xe, 0x4, 0x108, 0xb, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x5, 0x4, 0x10d, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x117, 0xa, 0x5, 
       0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x7, 0x5, 0x121, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x124, 
       0xb, 0x5, 0x5, 0x5, 0x126, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
       0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 
       0x137, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x13a, 0xb, 0x7, 0x3, 0x7, 0x3, 
       0x7, 0x5, 0x7, 0x13e, 0xa, 0x7, 0x5, 0x7, 0x140, 0xa, 0x7, 0x3, 0x7, 
       0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x146, 0xa, 0x7, 0x3, 0x8, 
       0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x14b, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 
       0x14e, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x153, 0xa, 
       0x9, 0xc, 0x9, 0xe, 0x9, 0x156, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 
       0xa, 0x7, 0xa, 0x15b, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x15e, 0xb, 0xa, 
       0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0x163, 0xa, 0xb, 0xc, 0xb, 
       0xe, 0xb, 0x166, 0xb, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 
       0x16b, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x16e, 0xb, 0xc, 0x3, 0xd, 0x3, 
       0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
       0xd, 0x5, 0xd, 0x17f, 0xa, 0xd, 0x3, 0xd, 0x5, 0xd, 0x182, 0xa, 0xd, 
       0x5, 0xd, 0x184, 0xa, 0xd, 0x3, 0xe, 0x5, 0xe, 0x187, 0xa, 0xe, 0x3, 
       0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x18c, 0xa, 0xe, 0x3, 0xe, 0x5, 
       0xe, 0x18f, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 
       0xe, 0x195, 0xa, 0xe, 0x3, 0xe, 0x5, 0xe, 0x198, 0xa, 0xe, 0x7, 0xe, 
       0x19a, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0x19d, 0xb, 0xe, 0x3, 0xe, 0x3, 
       0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x1a3, 0xa, 0xe, 0x3, 0xe, 0x3, 
       0xe, 0x5, 0xe, 0x1a7, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
       0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x7, 0x10, 0x1b0, 0xa, 0x10, 
       0xc, 0x10, 0xe, 0x10, 0x1b3, 0xb, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 
       0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x7, 0x11, 0x1bc, 
       0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 0x1bf, 0xb, 0x11, 0x5, 0x11, 0x1c1, 
       0xa, 0x11, 0x3, 0x11, 0x5, 0x11, 0x1c4, 0xa, 0x11, 0x3, 0x11, 0x3, 
       0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x5, 
       0x12, 0x1cd, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 
       0x3, 0x13, 0x5, 0x13, 0x1d4, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 
       0x13, 0x1d8, 0xa, 0x13, 0x3, 0x13, 0x7, 0x13, 0x1db, 0xa, 0x13, 0xc, 
       0x13, 0xe, 0x13, 0x1de, 0xb, 0x13, 0x3, 0x13, 0x5, 0x13, 0x1e1, 0xa, 
       0x13, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x1e5, 0xa, 0x14, 0x3, 0x14, 
       0x3, 0x14, 0x5, 0x14, 0x1e9, 0xa, 0x14, 0x3, 0x14, 0x7, 0x14, 0x1ec, 
       0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0x1ef, 0xb, 0x14, 0x3, 0x14, 0x5, 
       0x14, 0x1f2, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0x1f6, 0xa, 
       0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0x1fa, 0xa, 0x15, 0x3, 0x15, 
       0x7, 0x15, 0x1fd, 0xa, 0x15, 0xc, 0x15, 0xe, 0x15, 0x200, 0xb, 0x15, 
       0x3, 0x15, 0x5, 0x15, 0x203, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 0x5, 
       0x16, 0x207, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0x20b, 0xa, 
       0x16, 0x3, 0x16, 0x7, 0x16, 0x20e, 0xa, 0x16, 0xc, 0x16, 0xe, 0x16, 
       0x211, 0xb, 0x16, 0x3, 0x16, 0x5, 0x16, 0x214, 0xa, 0x16, 0x3, 0x17, 
       0x3, 0x17, 0x5, 0x17, 0x218, 0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 
       0x17, 0x21c, 0xa, 0x17, 0x3, 0x17, 0x7, 0x17, 0x21f, 0xa, 0x17, 0xc, 
       0x17, 0xe, 0x17, 0x222, 0xb, 0x17, 0x3, 0x17, 0x5, 0x17, 0x225, 0xa, 
       0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
       0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 
       0x18, 0x232, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x236, 0xa, 
       0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x23a, 0xa, 0x18, 0x3, 0x18, 
       0x3, 0x18, 0x5, 0x18, 0x23e, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 
       0x18, 0x242, 0xa, 0x18, 0x3, 0x18, 0x5, 0x18, 0x245, 0xa, 0x18, 0x3, 
       0x18, 0x5, 0x18, 0x248, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 
       0x24c, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x250, 0xa, 0x18, 
       0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x254, 0xa, 0x18, 0x3, 0x19, 0x5, 
       0x19, 0x257, 0xa, 0x19, 0x3, 0x19, 0x5, 0x19, 0x25a, 0xa, 0x19, 0x3, 
       0x19, 0x3, 0x19, 0x5, 0x19, 0x25e, 0xa, 0x19, 0x3, 0x19, 0x5, 0x19, 
       0x261, 0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x265, 0xa, 0x19, 
       0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x269, 0xa, 0x19, 0x3, 0x19, 0x5, 
       0x19, 0x26c, 0xa, 0x19, 0x7, 0x19, 0x26e, 0xa, 0x19, 0xc, 0x19, 0xe, 
       0x19, 0x271, 0xb, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x275, 0xa, 
       0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 
       0x19, 0x27c, 0xa, 0x19, 0x5, 0x19, 0x27e, 0xa, 0x19, 0x3, 0x1a, 0x3, 
       0x1a, 0x5, 0x1a, 0x282, 0xa, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 
       0x286, 0xa, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x5, 
       0x1b, 0x28c, 0xa, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x290, 0xa, 
       0x1b, 0x3, 0x1b, 0x7, 0x1b, 0x293, 0xa, 0x1b, 0xc, 0x1b, 0xe, 0x1b, 
       0x296, 0xb, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x299, 0xa, 0x1b, 0x3, 0x1c, 
       0x3, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 0x29e, 0xa, 0x1c, 0xc, 0x1c, 0xe, 
       0x1c, 0x2a1, 0xb, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 
       0x2a6, 0xa, 0x1c, 0xc, 0x1c, 0xe, 0x1c, 0x2a9, 0xb, 0x1c, 0x3, 0x1c, 
       0x3, 0x1c, 0x5, 0x1c, 0x2ad, 0xa, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 0x2b0, 
       0xa, 0x1c, 0xc, 0x1c, 0xe, 0x1c, 0x2b3, 0xb, 0x1c, 0x3, 0x1c, 0x3, 
       0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x5, 0x1d, 0x2ba, 0xa, 0x1d, 
       0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 
       0x7, 0x1e, 0x2c2, 0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 0x2c5, 0xb, 0x1e, 
       0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x2c9, 0xa, 0x1e, 0x3, 0x1e, 0x3, 
       0x1e, 0x5, 0x1e, 0x2cd, 0xa, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x2d0, 0xa, 
       0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x5, 0x1f, 0x2d6, 
       0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
       0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
       0x3, 0x20, 0x5, 0x20, 0x2e4, 0xa, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 
       0x21, 0x5, 0x21, 0x2e9, 0xa, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
       0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x2f1, 0xa, 0x22, 0x3, 
       0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x5, 
       0x23, 0x2f9, 0xa, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x5, 0x24, 
       0x2fe, 0xa, 0x24, 0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x302, 0xa, 0x24, 
       0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x306, 0xa, 0x24, 0x3, 0x24, 0x7, 
       0x24, 0x309, 0xa, 0x24, 0xc, 0x24, 0xe, 0x24, 0x30c, 0xb, 0x24, 0x3, 
       0x24, 0x5, 0x24, 0x30f, 0xa, 0x24, 0x3, 0x25, 0x5, 0x25, 0x312, 0xa, 
       0x25, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 0x316, 0xa, 0x25, 0x3, 0x25, 
       0x3, 0x25, 0x5, 0x25, 0x31a, 0xa, 0x25, 0x3, 0x25, 0x7, 0x25, 0x31d, 
       0xa, 0x25, 0xc, 0x25, 0xe, 0x25, 0x320, 0xb, 0x25, 0x3, 0x25, 0x5, 
       0x25, 0x323, 0xa, 0x25, 0x3, 0x26, 0x5, 0x26, 0x326, 0xa, 0x26, 0x3, 
       0x26, 0x3, 0x26, 0x5, 0x26, 0x32a, 0xa, 0x26, 0x3, 0x26, 0x3, 0x26, 
       0x5, 0x26, 0x32e, 0xa, 0x26, 0x3, 0x26, 0x3, 0x26, 0x5, 0x26, 0x332, 
       0xa, 0x26, 0x3, 0x26, 0x5, 0x26, 0x335, 0xa, 0x26, 0x3, 0x26, 0x3, 
       0x26, 0x5, 0x26, 0x339, 0xa, 0x26, 0x5, 0x26, 0x33b, 0xa, 0x26, 0x3, 
       0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x340, 0xa, 0x27, 0x3, 0x27, 
       0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x345, 0xa, 0x27, 0x3, 0x27, 0x3, 
       0x27, 0x5, 0x27, 0x349, 0xa, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 
       0x34d, 0xa, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x351, 0xa, 0x27, 
       0x3, 0x27, 0x7, 0x27, 0x354, 0xa, 0x27, 0xc, 0x27, 0xe, 0x27, 0x357, 
       0xb, 0x27, 0x5, 0x27, 0x359, 0xa, 0x27, 0x3, 0x27, 0x5, 0x27, 0x35c, 
       0xa, 0x27, 0x3, 0x27, 0x5, 0x27, 0x35f, 0xa, 0x27, 0x5, 0x27, 0x361, 
       0xa, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 
       0x367, 0xa, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 
       0x28, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 0x370, 0xa, 0x28, 0x3, 0x29, 
       0x3, 0x29, 0x5, 0x29, 0x374, 0xa, 0x29, 0x3, 0x29, 0x3, 0x29, 0x5, 
       0x29, 0x378, 0xa, 0x29, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 0x37c, 0xa, 
       0x29, 0x3, 0x29, 0x5, 0x29, 0x37f, 0xa, 0x29, 0x3, 0x29, 0x5, 0x29, 
       0x382, 0xa, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x387, 
       0xa, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 
       0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x7, 0x2a, 0x392, 0xa, 
       0x2a, 0xc, 0x2a, 0xe, 0x2a, 0x395, 0xb, 0x2a, 0x5, 0x2a, 0x397, 0xa, 
       0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x7, 0x2a, 0x39c, 0xa, 0x2a, 
       0xc, 0x2a, 0xe, 0x2a, 0x39f, 0xb, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x7, 
       0x2a, 0x3a3, 0xa, 0x2a, 0xc, 0x2a, 0xe, 0x2a, 0x3a6, 0xb, 0x2a, 0x3, 
       0x2a, 0x3, 0x2a, 0x7, 0x2a, 0x3aa, 0xa, 0x2a, 0xc, 0x2a, 0xe, 0x2a, 
       0x3ad, 0xb, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x5, 
       0x2b, 0x3b3, 0xa, 0x2b, 0x3, 0x2b, 0x5, 0x2b, 0x3b6, 0xa, 0x2b, 0x3, 
       0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x3bc, 0xa, 0x2c, 
       0x3, 0x2c, 0x5, 0x2c, 0x3bf, 0xa, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 
       0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 
       0x2d, 0x7, 0x2d, 0x3ca, 0xa, 0x2d, 0xc, 0x2d, 0xe, 0x2d, 0x3cd, 0xb, 
       0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x3d1, 0xa, 0x2d, 0x3, 0x2d, 
       0x6, 0x2d, 0x3d4, 0xa, 0x2d, 0xd, 0x2d, 0xe, 0x2d, 0x3d5, 0x3, 0x2d, 
       0x3, 0x2d, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 
       0x5, 0x2e, 0x3df, 0xa, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 
       0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x30, 0x3, 0x30, 0x3, 
       0x30, 0x3, 0x30, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 
       0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x32, 0x3, 0x33, 0x3, 0x33, 0x3, 
       0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x7, 0x33, 0x3fa, 0xa, 0x33, 
       0xc, 0x33, 0xe, 0x33, 0x3fd, 0xb, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 
       0x34, 0x5, 0x34, 0x402, 0xa, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x35, 
       0x3, 0x35, 0x3, 0x35, 0x5, 0x35, 0x409, 0xa, 0x35, 0x3, 0x36, 0x3, 
       0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x7, 0x36, 0x410, 0xa, 0x36, 
       0xc, 0x36, 0xe, 0x36, 0x413, 0xb, 0x36, 0x5, 0x36, 0x415, 0xa, 0x36, 
       0x3, 0x36, 0x5, 0x36, 0x418, 0xa, 0x36, 0x3, 0x36, 0x6, 0x36, 0x41b, 
       0xa, 0x36, 0xd, 0x36, 0xe, 0x36, 0x41c, 0x3, 0x36, 0x3, 0x36, 0x3, 
       0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x5, 
       0x36, 0x427, 0xa, 0x36, 0x3, 0x36, 0x5, 0x36, 0x42a, 0xa, 0x36, 0x3, 
       0x37, 0x3, 0x37, 0x3, 0x37, 0x5, 0x37, 0x42f, 0xa, 0x37, 0x3, 0x37, 
       0x5, 0x37, 0x432, 0xa, 0x37, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 
       0x38, 0x3, 0x38, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
       0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
       0x39, 0x5, 0x39, 0x444, 0xa, 0x39, 0x5, 0x39, 0x446, 0xa, 0x39, 0x3, 
       0x39, 0x3, 0x39, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 
       0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 
       0x3b, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 0x458, 0xa, 0x3c, 
       0x3, 0x3d, 0x3, 0x3d, 0x5, 0x3d, 0x45c, 0xa, 0x3d, 0x3, 0x3e, 0x3, 
       0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 
       0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 
       0x3f, 0x3, 0x40, 0x6, 0x40, 0x46d, 0xa, 0x40, 0xd, 0x40, 0xe, 0x40, 
       0x46e, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 
       0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x47a, 0xa, 0x40, 
       0xc, 0x40, 0xe, 0x40, 0x47d, 0xb, 0x40, 0x5, 0x40, 0x47f, 0xa, 0x40, 
       0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x484, 0xa, 0x40, 0xc, 
       0x40, 0xe, 0x40, 0x487, 0xb, 0x40, 0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 
       0x48b, 0xa, 0x40, 0xc, 0x40, 0xe, 0x40, 0x48e, 0xb, 0x40, 0x3, 0x40, 
       0x6, 0x40, 0x491, 0xa, 0x40, 0xd, 0x40, 0xe, 0x40, 0x492, 0x3, 0x41, 
       0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 0x7, 0x41, 0x499, 0xa, 0x41, 0xc, 
       0x41, 0xe, 0x41, 0x49c, 0xb, 0x41, 0x5, 0x41, 0x49e, 0xa, 0x41, 0x3, 
       0x42, 0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x4a3, 0xa, 0x42, 0x3, 0x42, 
       0x3, 0x42, 0x7, 0x42, 0x4a7, 0xa, 0x42, 0xc, 0x42, 0xe, 0x42, 0x4aa, 
       0xb, 0x42, 0x5, 0x42, 0x4ac, 0xa, 0x42, 0x3, 0x43, 0x3, 0x43, 0x3, 
       0x43, 0x7, 0x43, 0x4b1, 0xa, 0x43, 0xc, 0x43, 0xe, 0x43, 0x4b4, 0xb, 
       0x43, 0x3, 0x44, 0x3, 0x44, 0x5, 0x44, 0x4b8, 0xa, 0x44, 0x3, 0x45, 
       0x3, 0x45, 0x3, 0x45, 0x7, 0x45, 0x4bd, 0xa, 0x45, 0xc, 0x45, 0xe, 
       0x45, 0x4c0, 0xb, 0x45, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 
       0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x48, 
       0x3, 0x48, 0x5, 0x48, 0x4cd, 0xa, 0x48, 0x3, 0x48, 0x3, 0x48, 0x5, 
       0x48, 0x4d1, 0xa, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x49, 0x3, 0x49, 
       0x3, 0x49, 0x3, 0x49, 0x7, 0x49, 0x4d9, 0xa, 0x49, 0xc, 0x49, 0xe, 
       0x49, 0x4dc, 0xb, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x4a, 0x7, 0x4a, 
       0x4e1, 0xa, 0x4a, 0xc, 0x4a, 0xe, 0x4a, 0x4e4, 0xb, 0x4a, 0x3, 0x4a, 
       0x5, 0x4a, 0x4e7, 0xa, 0x4a, 0x3, 0x4a, 0x3, 0x4a, 0x5, 0x4a, 0x4eb, 
       0xa, 0x4a, 0x3, 0x4a, 0x3, 0x4a, 0x5, 0x4a, 0x4ef, 0xa, 0x4a, 0x3, 
       0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x5, 0x4b, 0x4f6, 
       0xa, 0x4b, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 
       0x4fc, 0xa, 0x4c, 0x5, 0x4c, 0x4fe, 0xa, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 
       0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x505, 0xa, 0x4d, 0x3, 
       0x4e, 0x3, 0x4e, 0x7, 0x4e, 0x509, 0xa, 0x4e, 0xc, 0x4e, 0xe, 0x4e, 
       0x50c, 0xb, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x7, 0x4e, 0x510, 0xa, 0x4e, 
       0xc, 0x4e, 0xe, 0x4e, 0x513, 0xb, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x7, 
       0x4e, 0x517, 0xa, 0x4e, 0xc, 0x4e, 0xe, 0x4e, 0x51a, 0xb, 0x4e, 0x3, 
       0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x5, 0x4e, 0x51f, 0xa, 0x4e, 0x3, 0x4f, 
       0x3, 0x4f, 0x7, 0x4f, 0x523, 0xa, 0x4f, 0xc, 0x4f, 0xe, 0x4f, 0x526, 
       0xb, 0x4f, 0x3, 0x4f, 0x5, 0x4f, 0x529, 0xa, 0x4f, 0x3, 0x4f, 0x3, 
       0x4f, 0x3, 0x50, 0x3, 0x50, 0x3, 0x50, 0x5, 0x50, 0x530, 0xa, 0x50, 
       0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x5, 0x51, 0x536, 0xa, 
       0x51, 0x3, 0x52, 0x3, 0x52, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 
       0x53, 0x5, 0x53, 0x53e, 0xa, 0x53, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 
       0x5, 0x54, 0x543, 0xa, 0x54, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 
       0x55, 0x5, 0x55, 0x549, 0xa, 0x55, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 
       0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x5, 0x56, 0x551, 0xa, 0x56, 0x5, 
       0x56, 0x553, 0xa, 0x56, 0x3, 0x57, 0x3, 0x57, 0x3, 0x57, 0x3, 0x57, 
       0x7, 0x57, 0x559, 0xa, 0x57, 0xc, 0x57, 0xe, 0x57, 0x55c, 0xb, 0x57, 
       0x3, 0x58, 0x3, 0x58, 0x3, 0x59, 0x5, 0x59, 0x561, 0xa, 0x59, 0x3, 
       0x59, 0x3, 0x59, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 
       0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x5, 0x5a, 0x56d, 0xa, 0x5a, 
       0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 0x7, 0x5b, 0x573, 0xa, 
       0x5b, 0xc, 0x5b, 0xe, 0x5b, 0x576, 0xb, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 
       0x5, 0x5b, 0x57a, 0xa, 0x5b, 0x5, 0x5b, 0x57c, 0xa, 0x5b, 0x3, 0x5b, 
       0x3, 0x5b, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 
       0x7, 0x5c, 0x585, 0xa, 0x5c, 0xc, 0x5c, 0xe, 0x5c, 0x588, 0xb, 0x5c, 
       0x5, 0x5c, 0x58a, 0xa, 0x5c, 0x3, 0x5c, 0x5, 0x5c, 0x58d, 0xa, 0x5c, 
       0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x5, 0x5d, 
       0x594, 0xa, 0x5d, 0x5, 0x5d, 0x596, 0xa, 0x5d, 0x3, 0x5e, 0x3, 0x5e, 
       0x7, 0x5e, 0x59a, 0xa, 0x5e, 0xc, 0x5e, 0xe, 0x5e, 0x59d, 0xb, 0x5e, 
       0x3, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 0x7, 0x5e, 0x5a2, 0xa, 0x5e, 0xc, 
       0x5e, 0xe, 0x5e, 0x5a5, 0xb, 0x5e, 0x3, 0x5e, 0x7, 0x5e, 0x5a8, 0xa, 
       0x5e, 0xc, 0x5e, 0xe, 0x5e, 0x5ab, 0xb, 0x5e, 0x3, 0x5e, 0x7, 0x5e, 
       0x5ae, 0xa, 0x5e, 0xc, 0x5e, 0xe, 0x5e, 0x5b1, 0xb, 0x5e, 0x3, 0x5e, 
       0x3, 0x5e, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x60, 0x6, 0x60, 0x5b8, 0xa, 
       0x60, 0xd, 0x60, 0xe, 0x60, 0x5b9, 0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 
       0x5, 0x61, 0x5bf, 0xa, 0x61, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 
       0x62, 0x3, 0x62, 0x3, 0x62, 0x3, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 
       0x63, 0x3, 0x63, 0x7, 0x63, 0x5cc, 0xa, 0x63, 0xc, 0x63, 0xe, 0x63, 
       0x5cf, 0xb, 0x63, 0x3, 0x63, 0x3, 0x63, 0x3, 0x64, 0x6, 0x64, 0x5d4, 
       0xa, 0x64, 0xd, 0x64, 0xe, 0x64, 0x5d5, 0x3, 0x64, 0x3, 0x64, 0x3, 
       0x64, 0x3, 0x64, 0x7, 0x64, 0x5dc, 0xa, 0x64, 0xc, 0x64, 0xe, 0x64, 
       0x5df, 0xb, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x65, 0x5, 0x65, 0x5e4, 
       0xa, 0x65, 0x3, 0x65, 0x7, 0x65, 0x5e7, 0xa, 0x65, 0xc, 0x65, 0xe, 
       0x65, 0x5ea, 0xb, 0x65, 0x3, 0x65, 0x3, 0x65, 0x5, 0x65, 0x5ee, 0xa, 
       0x65, 0x3, 0x65, 0x7, 0x65, 0x5f1, 0xa, 0x65, 0xc, 0x65, 0xe, 0x65, 
       0x5f4, 0xb, 0x65, 0x3, 0x65, 0x3, 0x65, 0x3, 0x65, 0x3, 0x65, 0x3, 
       0x65, 0x7, 0x65, 0x5fb, 0xa, 0x65, 0xc, 0x65, 0xe, 0x65, 0x5fe, 0xb, 
       0x65, 0x5, 0x65, 0x600, 0xa, 0x65, 0x3, 0x65, 0x3, 0x65, 0x3, 0x65, 
       0x7, 0x65, 0x605, 0xa, 0x65, 0xc, 0x65, 0xe, 0x65, 0x608, 0xb, 0x65, 
       0x3, 0x65, 0x3, 0x65, 0x3, 0x66, 0x7, 0x66, 0x60d, 0xa, 0x66, 0xc, 
       0x66, 0xe, 0x66, 0x610, 0xb, 0x66, 0x3, 0x66, 0x3, 0x66, 0x3, 0x66, 
       0x5, 0x66, 0x615, 0xa, 0x66, 0x3, 0x66, 0x5, 0x66, 0x618, 0xa, 0x66, 
       0x3, 0x66, 0x3, 0x66, 0x7, 0x66, 0x61c, 0xa, 0x66, 0xc, 0x66, 0xe, 
       0x66, 0x61f, 0xb, 0x66, 0x3, 0x66, 0x3, 0x66, 0x3, 0x67, 0x3, 0x67, 
       0x7, 0x67, 0x625, 0xa, 0x67, 0xc, 0x67, 0xe, 0x67, 0x628, 0xb, 0x67, 
       0x3, 0x67, 0x3, 0x67, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x7, 0xfd, 
       0x106, 0x5e8, 0x5f2, 0x60e, 0x2, 0x69, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 
       0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 
       0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 
       0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 
       0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 
       0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 
       0x7c, 0x7e, 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 
       0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 0xa6, 
       0xa8, 0xaa, 0xac, 0xae, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 
       0xbe, 0xc0, 0xc2, 0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce, 0x2, 0x12, 
       0x4, 0x2, 0x55, 0x57, 0x59, 0x5b, 0x3, 0x2, 0x4d, 0x4e, 0x3, 0x2, 
       0x4b, 0x4c, 0x4, 0x2, 0x3e, 0x3e, 0x4e, 0x4e, 0x4, 0x2, 0x4d, 0x4d, 
       0x67, 0x67, 0x5, 0x2, 0x37, 0x3a, 0x5e, 0x5e, 0x67, 0x67, 0x5, 0x2, 
       0x5, 0x5, 0x7, 0x7, 0x67, 0x67, 0x4, 0x2, 0x5, 0x5, 0x7, 0x7, 0x3, 
       0x2, 0x72, 0x72, 0x4, 0x2, 0x5, 0x5, 0x67, 0x67, 0x4, 0x2, 0x5e, 
       0x5e, 0x63, 0x63, 0x3, 0x2, 0x56, 0x5b, 0x7, 0x2, 0x46, 0x46, 0x48, 
       0x48, 0x55, 0x5b, 0x5f, 0x5f, 0x63, 0x63, 0x4, 0x2, 0x3c, 0x3c, 0x42, 
       0x42, 0x4, 0x2, 0x5f, 0x5f, 0x64, 0x64, 0x4, 0x2, 0x5, 0x8, 0xa, 
       0xc, 0x2, 0x6f3, 0x2, 0xd1, 0x3, 0x2, 0x2, 0x2, 0x4, 0xd7, 0x3, 0x2, 
       0x2, 0x2, 0x6, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x8, 0x10e, 0x3, 0x2, 0x2, 
       0x2, 0xa, 0x12c, 0x3, 0x2, 0x2, 0x2, 0xc, 0x145, 0x3, 0x2, 0x2, 0x2, 
       0xe, 0x147, 0x3, 0x2, 0x2, 0x2, 0x10, 0x14f, 0x3, 0x2, 0x2, 0x2, 
       0x12, 0x157, 0x3, 0x2, 0x2, 0x2, 0x14, 0x15f, 0x3, 0x2, 0x2, 0x2, 
       0x16, 0x167, 0x3, 0x2, 0x2, 0x2, 0x18, 0x183, 0x3, 0x2, 0x2, 0x2, 
       0x1a, 0x186, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x1a8, 0x3, 0x2, 0x2, 0x2, 
       0x1e, 0x1ac, 0x3, 0x2, 0x2, 0x2, 0x20, 0x1b4, 0x3, 0x2, 0x2, 0x2, 
       0x22, 0x1cc, 0x3, 0x2, 0x2, 0x2, 0x24, 0x1d1, 0x3, 0x2, 0x2, 0x2, 
       0x26, 0x1e2, 0x3, 0x2, 0x2, 0x2, 0x28, 0x1f3, 0x3, 0x2, 0x2, 0x2, 
       0x2a, 0x204, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x215, 0x3, 0x2, 0x2, 0x2, 
       0x2e, 0x253, 0x3, 0x2, 0x2, 0x2, 0x30, 0x256, 0x3, 0x2, 0x2, 0x2, 
       0x32, 0x27f, 0x3, 0x2, 0x2, 0x2, 0x34, 0x289, 0x3, 0x2, 0x2, 0x2, 
       0x36, 0x29a, 0x3, 0x2, 0x2, 0x2, 0x38, 0x2b9, 0x3, 0x2, 0x2, 0x2, 
       0x3a, 0x2bd, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x2d5, 0x3, 0x2, 0x2, 0x2, 
       0x3e, 0x2d7, 0x3, 0x2, 0x2, 0x2, 0x40, 0x2e5, 0x3, 0x2, 0x2, 0x2, 
       0x42, 0x2ed, 0x3, 0x2, 0x2, 0x2, 0x44, 0x2f5, 0x3, 0x2, 0x2, 0x2, 
       0x46, 0x2fd, 0x3, 0x2, 0x2, 0x2, 0x48, 0x311, 0x3, 0x2, 0x2, 0x2, 
       0x4a, 0x33a, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x360, 0x3, 0x2, 0x2, 0x2, 
       0x4e, 0x36f, 0x3, 0x2, 0x2, 0x2, 0x50, 0x371, 0x3, 0x2, 0x2, 0x2, 
       0x52, 0x383, 0x3, 0x2, 0x2, 0x2, 0x54, 0x3ae, 0x3, 0x2, 0x2, 0x2, 
       0x56, 0x3be, 0x3, 0x2, 0x2, 0x2, 0x58, 0x3c0, 0x3, 0x2, 0x2, 0x2, 
       0x5a, 0x3d9, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x3e3, 0x3, 0x2, 0x2, 0x2, 
       0x5e, 0x3e7, 0x3, 0x2, 0x2, 0x2, 0x60, 0x3eb, 0x3, 0x2, 0x2, 0x2, 
       0x62, 0x3ef, 0x3, 0x2, 0x2, 0x2, 0x64, 0x3f3, 0x3, 0x2, 0x2, 0x2, 
       0x66, 0x401, 0x3, 0x2, 0x2, 0x2, 0x68, 0x408, 0x3, 0x2, 0x2, 0x2, 
       0x6a, 0x426, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x42e, 0x3, 0x2, 0x2, 0x2, 
       0x6e, 0x433, 0x3, 0x2, 0x2, 0x2, 0x70, 0x438, 0x3, 0x2, 0x2, 0x2, 
       0x72, 0x449, 0x3, 0x2, 0x2, 0x2, 0x74, 0x450, 0x3, 0x2, 0x2, 0x2, 
       0x76, 0x457, 0x3, 0x2, 0x2, 0x2, 0x78, 0x45b, 0x3, 0x2, 0x2, 0x2, 
       0x7a, 0x45d, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x464, 0x3, 0x2, 0x2, 0x2, 
       0x7e, 0x46c, 0x3, 0x2, 0x2, 0x2, 0x80, 0x494, 0x3, 0x2, 0x2, 0x2, 
       0x82, 0x49f, 0x3, 0x2, 0x2, 0x2, 0x84, 0x4ad, 0x3, 0x2, 0x2, 0x2, 
       0x86, 0x4b7, 0x3, 0x2, 0x2, 0x2, 0x88, 0x4b9, 0x3, 0x2, 0x2, 0x2, 
       0x8a, 0x4c1, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x4c5, 0x3, 0x2, 0x2, 0x2, 
       0x8e, 0x4ca, 0x3, 0x2, 0x2, 0x2, 0x90, 0x4d4, 0x3, 0x2, 0x2, 0x2, 
       0x92, 0x4e2, 0x3, 0x2, 0x2, 0x2, 0x94, 0x4f5, 0x3, 0x2, 0x2, 0x2, 
       0x96, 0x4f7, 0x3, 0x2, 0x2, 0x2, 0x98, 0x501, 0x3, 0x2, 0x2, 0x2, 
       0x9a, 0x51e, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x520, 0x3, 0x2, 0x2, 0x2, 
       0x9e, 0x52c, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x531, 0x3, 0x2, 0x2, 0x2, 
       0xa2, 0x537, 0x3, 0x2, 0x2, 0x2, 0xa4, 0x539, 0x3, 0x2, 0x2, 0x2, 
       0xa6, 0x542, 0x3, 0x2, 0x2, 0x2, 0xa8, 0x544, 0x3, 0x2, 0x2, 0x2, 
       0xaa, 0x552, 0x3, 0x2, 0x2, 0x2, 0xac, 0x554, 0x3, 0x2, 0x2, 0x2, 
       0xae, 0x55d, 0x3, 0x2, 0x2, 0x2, 0xb0, 0x560, 0x3, 0x2, 0x2, 0x2, 
       0xb2, 0x56c, 0x3, 0x2, 0x2, 0x2, 0xb4, 0x56e, 0x3, 0x2, 0x2, 0x2, 
       0xb6, 0x57f, 0x3, 0x2, 0x2, 0x2, 0xb8, 0x595, 0x3, 0x2, 0x2, 0x2, 
       0xba, 0x597, 0x3, 0x2, 0x2, 0x2, 0xbc, 0x5b4, 0x3, 0x2, 0x2, 0x2, 
       0xbe, 0x5b7, 0x3, 0x2, 0x2, 0x2, 0xc0, 0x5be, 0x3, 0x2, 0x2, 0x2, 
       0xc2, 0x5c0, 0x3, 0x2, 0x2, 0x2, 0xc4, 0x5c6, 0x3, 0x2, 0x2, 0x2, 
       0xc6, 0x5d3, 0x3, 0x2, 0x2, 0x2, 0xc8, 0x5e3, 0x3, 0x2, 0x2, 0x2, 
       0xca, 0x60e, 0x3, 0x2, 0x2, 0x2, 0xcc, 0x622, 0x3, 0x2, 0x2, 0x2, 
       0xce, 0x62b, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xd2, 0x5, 0x4, 0x3, 0x2, 
       0xd1, 0xd0, 0x3, 0x2, 0x2, 0x2, 0xd1, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd2, 
       0xd3, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd4, 0x7, 0x2, 0x2, 0x3, 0xd4, 0xd5, 
       0x8, 0x2, 0x1, 0x2, 0xd5, 0x3, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xd8, 0x5, 
       0x6, 0x4, 0x2, 0xd7, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xd9, 0x3, 0x2, 
       0x2, 0x2, 0xd9, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x3, 0x2, 0x2, 
       0x2, 0xda, 0x5, 0x3, 0x2, 0x2, 0x2, 0xdb, 0x10d, 0x5, 0x52, 0x2a, 
       0x2, 0xdc, 0xdd, 0x7, 0xd, 0x2, 0x2, 0xdd, 0x10d, 0x8, 0x4, 0x1, 
       0x2, 0xde, 0x10d, 0x5, 0x58, 0x2d, 0x2, 0xdf, 0xe0, 0x7, 0xe, 0x2, 
       0x2, 0xe0, 0x10d, 0x8, 0x4, 0x1, 0x2, 0xe1, 0x10d, 0x5, 0x5a, 0x2e, 
       0x2, 0xe2, 0xe3, 0x7, 0x14, 0x2, 0x2, 0xe3, 0x10d, 0x8, 0x4, 0x1, 
       0x2, 0xe4, 0x10d, 0x5, 0x5c, 0x2f, 0x2, 0xe5, 0xe6, 0x7, 0x15, 0x2, 
       0x2, 0xe6, 0x10d, 0x8, 0x4, 0x1, 0x2, 0xe7, 0x10d, 0x5, 0x5e, 0x30, 
       0x2, 0xe8, 0xe9, 0x7, 0x16, 0x2, 0x2, 0xe9, 0x10d, 0x8, 0x4, 0x1, 
       0x2, 0xea, 0x10d, 0x5, 0x60, 0x31, 0x2, 0xeb, 0xec, 0x7, 0x17, 0x2, 
       0x2, 0xec, 0x10d, 0x8, 0x4, 0x1, 0x2, 0xed, 0x10d, 0x5, 0x62, 0x32, 
       0x2, 0xee, 0xef, 0x7, 0x18, 0x2, 0x2, 0xef, 0x10d, 0x8, 0x4, 0x1, 
       0x2, 0xf0, 0x10d, 0x5, 0x8, 0x5, 0x2, 0xf1, 0xf2, 0x7, 0x19, 0x2, 
       0x2, 0xf2, 0x10d, 0x8, 0x4, 0x1, 0x2, 0xf3, 0x10d, 0x5, 0x20, 0x11, 
       0x2, 0xf4, 0xf5, 0x7, 0x1a, 0x2, 0x2, 0xf5, 0x10d, 0x8, 0x4, 0x1, 
       0x2, 0xf6, 0x10d, 0x5, 0xc8, 0x65, 0x2, 0xf7, 0xf9, 0x5, 0xc6, 0x64, 
       0x2, 0xf8, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xf9, 0x3, 0x2, 0x2, 0x2, 
       0xf9, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfc, 0x5, 0xc4, 0x63, 0x2, 
       0xfb, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xff, 0x3, 0x2, 0x2, 0x2, 0xfd, 
       0xfe, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xfe, 0x100, 
       0x3, 0x2, 0x2, 0x2, 0xff, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x100, 0x101, 
       0x7, 0x1f, 0x2, 0x2, 0x101, 0x10d, 0x8, 0x4, 0x1, 0x2, 0x102, 0x10d, 
       0x5, 0xca, 0x66, 0x2, 0x103, 0x105, 0x5, 0xc4, 0x63, 0x2, 0x104, 
       0x103, 0x3, 0x2, 0x2, 0x2, 0x105, 0x108, 0x3, 0x2, 0x2, 0x2, 0x106, 
       0x107, 0x3, 0x2, 0x2, 0x2, 0x106, 0x104, 0x3, 0x2, 0x2, 0x2, 0x107, 
       0x109, 0x3, 0x2, 0x2, 0x2, 0x108, 0x106, 0x3, 0x2, 0x2, 0x2, 0x109, 
       0x10a, 0x7, 0x20, 0x2, 0x2, 0x10a, 0x10d, 0x8, 0x4, 0x1, 0x2, 0x10b, 
       0x10d, 0x5, 0xcc, 0x67, 0x2, 0x10c, 0xdb, 0x3, 0x2, 0x2, 0x2, 0x10c, 
       0xdc, 0x3, 0x2, 0x2, 0x2, 0x10c, 0xde, 0x3, 0x2, 0x2, 0x2, 0x10c, 
       0xdf, 0x3, 0x2, 0x2, 0x2, 0x10c, 0xe1, 0x3, 0x2, 0x2, 0x2, 0x10c, 
       0xe2, 0x3, 0x2, 0x2, 0x2, 0x10c, 0xe4, 0x3, 0x2, 0x2, 0x2, 0x10c, 
       0xe5, 0x3, 0x2, 0x2, 0x2, 0x10c, 0xe7, 0x3, 0x2, 0x2, 0x2, 0x10c, 
       0xe8, 0x3, 0x2, 0x2, 0x2, 0x10c, 0xea, 0x3, 0x2, 0x2, 0x2, 0x10c, 
       0xeb, 0x3, 0x2, 0x2, 0x2, 0x10c, 0xed, 0x3, 0x2, 0x2, 0x2, 0x10c, 
       0xee, 0x3, 0x2, 0x2, 0x2, 0x10c, 0xf0, 0x3, 0x2, 0x2, 0x2, 0x10c, 
       0xf1, 0x3, 0x2, 0x2, 0x2, 0x10c, 0xf3, 0x3, 0x2, 0x2, 0x2, 0x10c, 
       0xf4, 0x3, 0x2, 0x2, 0x2, 0x10c, 0xf6, 0x3, 0x2, 0x2, 0x2, 0x10c, 
       0xf8, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x102, 0x3, 0x2, 0x2, 0x2, 0x10c, 
       0x106, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x10d, 
       0x7, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x10f, 0x7, 0x19, 0x2, 0x2, 0x10f, 
       0x110, 0x8, 0x5, 0x1, 0x2, 0x110, 0x111, 0x7, 0x67, 0x2, 0x2, 0x111, 
       0x112, 0x8, 0x5, 0x1, 0x2, 0x112, 0x116, 0x7, 0x3d, 0x2, 0x2, 0x113, 
       0x117, 0x5, 0xa, 0x6, 0x2, 0x114, 0x115, 0x7, 0x67, 0x2, 0x2, 0x115, 
       0x117, 0x8, 0x5, 0x1, 0x2, 0x116, 0x113, 0x3, 0x2, 0x2, 0x2, 0x116, 
       0x114, 0x3, 0x2, 0x2, 0x2, 0x117, 0x118, 0x3, 0x2, 0x2, 0x2, 0x118, 
       0x119, 0x7, 0x37, 0x2, 0x2, 0x119, 0x125, 0x8, 0x5, 0x1, 0x2, 0x11a, 
       0x11b, 0x5, 0xc, 0x7, 0x2, 0x11b, 0x122, 0x8, 0x5, 0x1, 0x2, 0x11c, 
       0x11d, 0x7, 0x5e, 0x2, 0x2, 0x11d, 0x11e, 0x5, 0xc, 0x7, 0x2, 0x11e, 
       0x11f, 0x8, 0x5, 0x1, 0x2, 0x11f, 0x121, 0x3, 0x2, 0x2, 0x2, 0x120, 
       0x11c, 0x3, 0x2, 0x2, 0x2, 0x121, 0x124, 0x3, 0x2, 0x2, 0x2, 0x122, 
       0x120, 0x3, 0x2, 0x2, 0x2, 0x122, 0x123, 0x3, 0x2, 0x2, 0x2, 0x123, 
       0x126, 0x3, 0x2, 0x2, 0x2, 0x124, 0x122, 0x3, 0x2, 0x2, 0x2, 0x125, 
       0x11a, 0x3, 0x2, 0x2, 0x2, 0x125, 0x126, 0x3, 0x2, 0x2, 0x2, 0x126, 
       0x127, 0x3, 0x2, 0x2, 0x2, 0x127, 0x128, 0x7, 0x38, 0x2, 0x2, 0x128, 
       0x129, 0x8, 0x5, 0x1, 0x2, 0x129, 0x12a, 0x5, 0x36, 0x1c, 0x2, 0x12a, 
       0x12b, 0x8, 0x5, 0x1, 0x2, 0x12b, 0x9, 0x3, 0x2, 0x2, 0x2, 0x12c, 
       0x12d, 0x7, 0x39, 0x2, 0x2, 0x12d, 0x12e, 0x7, 0x67, 0x2, 0x2, 0x12e, 
       0x12f, 0x7, 0x3a, 0x2, 0x2, 0x12f, 0xb, 0x3, 0x2, 0x2, 0x2, 0x130, 
       0x146, 0x7, 0x6, 0x2, 0x2, 0x131, 0x146, 0x7, 0x9, 0x2, 0x2, 0x132, 
       0x13f, 0x7, 0x39, 0x2, 0x2, 0x133, 0x138, 0x5, 0xc, 0x7, 0x2, 0x134, 
       0x135, 0x7, 0x5e, 0x2, 0x2, 0x135, 0x137, 0x5, 0xc, 0x7, 0x2, 0x136, 
       0x134, 0x3, 0x2, 0x2, 0x2, 0x137, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x138, 
       0x136, 0x3, 0x2, 0x2, 0x2, 0x138, 0x139, 0x3, 0x2, 0x2, 0x2, 0x139, 
       0x13d, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x138, 0x3, 0x2, 0x2, 0x2, 0x13b, 
       0x13c, 0x7, 0x52, 0x2, 0x2, 0x13c, 0x13e, 0x5, 0xc, 0x7, 0x2, 0x13d, 
       0x13b, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x13e, 
       0x140, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x133, 0x3, 0x2, 0x2, 0x2, 0x13f, 
       0x140, 0x3, 0x2, 0x2, 0x2, 0x140, 0x141, 0x3, 0x2, 0x2, 0x2, 0x141, 
       0x146, 0x7, 0x3a, 0x2, 0x2, 0x142, 0x146, 0x5, 0xe, 0x8, 0x2, 0x143, 
       0x144, 0x8, 0x7, 0x1, 0x2, 0x144, 0x146, 0xb, 0x2, 0x2, 0x2, 0x145, 
       0x130, 0x3, 0x2, 0x2, 0x2, 0x145, 0x131, 0x3, 0x2, 0x2, 0x2, 0x145, 
       0x132, 0x3, 0x2, 0x2, 0x2, 0x145, 0x142, 0x3, 0x2, 0x2, 0x2, 0x145, 
       0x143, 0x3, 0x2, 0x2, 0x2, 0x146, 0xd, 0x3, 0x2, 0x2, 0x2, 0x147, 
       0x14c, 0x5, 0x10, 0x9, 0x2, 0x148, 0x149, 0x7, 0x41, 0x2, 0x2, 0x149, 
       0x14b, 0x5, 0x10, 0x9, 0x2, 0x14a, 0x148, 0x3, 0x2, 0x2, 0x2, 0x14b, 
       0x14e, 0x3, 0x2, 0x2, 0x2, 0x14c, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x14c, 
       0x14d, 0x3, 0x2, 0x2, 0x2, 0x14d, 0xf, 0x3, 0x2, 0x2, 0x2, 0x14e, 
       0x14c, 0x3, 0x2, 0x2, 0x2, 0x14f, 0x154, 0x5, 0x12, 0xa, 0x2, 0x150, 
       0x151, 0x7, 0x40, 0x2, 0x2, 0x151, 0x153, 0x5, 0x12, 0xa, 0x2, 0x152, 
       0x150, 0x3, 0x2, 0x2, 0x2, 0x153, 0x156, 0x3, 0x2, 0x2, 0x2, 0x154, 
       0x152, 0x3, 0x2, 0x2, 0x2, 0x154, 0x155, 0x3, 0x2, 0x2, 0x2, 0x155, 
       0x11, 0x3, 0x2, 0x2, 0x2, 0x156, 0x154, 0x3, 0x2, 0x2, 0x2, 0x157, 
       0x15c, 0x5, 0x14, 0xb, 0x2, 0x158, 0x159, 0x9, 0x2, 0x2, 0x2, 0x159, 
       0x15b, 0x5, 0x14, 0xb, 0x2, 0x15a, 0x158, 0x3, 0x2, 0x2, 0x2, 0x15b, 
       0x15e, 0x3, 0x2, 0x2, 0x2, 0x15c, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x15c, 
       0x15d, 0x3, 0x2, 0x2, 0x2, 0x15d, 0x13, 0x3, 0x2, 0x2, 0x2, 0x15e, 
       0x15c, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x164, 0x5, 0x16, 0xc, 0x2, 0x160, 
       0x161, 0x9, 0x3, 0x2, 0x2, 0x161, 0x163, 0x5, 0x16, 0xc, 0x2, 0x162, 
       0x160, 0x3, 0x2, 0x2, 0x2, 0x163, 0x166, 0x3, 0x2, 0x2, 0x2, 0x164, 
       0x162, 0x3, 0x2, 0x2, 0x2, 0x164, 0x165, 0x3, 0x2, 0x2, 0x2, 0x165, 
       0x15, 0x3, 0x2, 0x2, 0x2, 0x166, 0x164, 0x3, 0x2, 0x2, 0x2, 0x167, 
       0x16c, 0x5, 0x18, 0xd, 0x2, 0x168, 0x169, 0x9, 0x4, 0x2, 0x2, 0x169, 
       0x16b, 0x5, 0x18, 0xd, 0x2, 0x16a, 0x168, 0x3, 0x2, 0x2, 0x2, 0x16b, 
       0x16e, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x16c, 
       0x16d, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x17, 0x3, 0x2, 0x2, 0x2, 0x16e, 
       0x16c, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x184, 0x7, 0x8, 0x2, 0x2, 0x170, 
       0x184, 0x7, 0x6, 0x2, 0x2, 0x171, 0x184, 0x7, 0x9, 0x2, 0x2, 0x172, 
       0x184, 0x7, 0x5, 0x2, 0x2, 0x173, 0x184, 0x7, 0x7, 0x2, 0x2, 0x174, 
       0x184, 0x7, 0x1e, 0x2, 0x2, 0x175, 0x184, 0x7, 0x26, 0x2, 0x2, 0x176, 
       0x177, 0x7, 0x37, 0x2, 0x2, 0x177, 0x178, 0x5, 0xe, 0x8, 0x2, 0x178, 
       0x179, 0x7, 0x38, 0x2, 0x2, 0x179, 0x184, 0x3, 0x2, 0x2, 0x2, 0x17a, 
       0x184, 0x5, 0x1a, 0xe, 0x2, 0x17b, 0x181, 0x7, 0x67, 0x2, 0x2, 0x17c, 
       0x17e, 0x7, 0x37, 0x2, 0x2, 0x17d, 0x17f, 0x5, 0x1e, 0x10, 0x2, 0x17e, 
       0x17d, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x17f, 
       0x180, 0x3, 0x2, 0x2, 0x2, 0x180, 0x182, 0x7, 0x38, 0x2, 0x2, 0x181, 
       0x17c, 0x3, 0x2, 0x2, 0x2, 0x181, 0x182, 0x3, 0x2, 0x2, 0x2, 0x182, 
       0x184, 0x3, 0x2, 0x2, 0x2, 0x183, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x183, 
       0x170, 0x3, 0x2, 0x2, 0x2, 0x183, 0x171, 0x3, 0x2, 0x2, 0x2, 0x183, 
       0x172, 0x3, 0x2, 0x2, 0x2, 0x183, 0x173, 0x3, 0x2, 0x2, 0x2, 0x183, 
       0x174, 0x3, 0x2, 0x2, 0x2, 0x183, 0x175, 0x3, 0x2, 0x2, 0x2, 0x183, 
       0x176, 0x3, 0x2, 0x2, 0x2, 0x183, 0x17a, 0x3, 0x2, 0x2, 0x2, 0x183, 
       0x17b, 0x3, 0x2, 0x2, 0x2, 0x184, 0x19, 0x3, 0x2, 0x2, 0x2, 0x185, 
       0x187, 0x9, 0x5, 0x2, 0x2, 0x186, 0x185, 0x3, 0x2, 0x2, 0x2, 0x186, 
       0x187, 0x3, 0x2, 0x2, 0x2, 0x187, 0x18b, 0x3, 0x2, 0x2, 0x2, 0x188, 
       0x189, 0x7, 0x67, 0x2, 0x2, 0x189, 0x18c, 0x8, 0xe, 0x1, 0x2, 0x18a, 
       0x18c, 0x7, 0x4d, 0x2, 0x2, 0x18b, 0x188, 0x3, 0x2, 0x2, 0x2, 0x18b, 
       0x18a, 0x3, 0x2, 0x2, 0x2, 0x18c, 0x18e, 0x3, 0x2, 0x2, 0x2, 0x18d, 
       0x18f, 0x5, 0x1c, 0xf, 0x2, 0x18e, 0x18d, 0x3, 0x2, 0x2, 0x2, 0x18e, 
       0x18f, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x19b, 0x3, 0x2, 0x2, 0x2, 0x190, 
       0x194, 0x9, 0x5, 0x2, 0x2, 0x191, 0x192, 0x7, 0x67, 0x2, 0x2, 0x192, 
       0x195, 0x8, 0xe, 0x1, 0x2, 0x193, 0x195, 0x7, 0x4d, 0x2, 0x2, 0x194, 
       0x191, 0x3, 0x2, 0x2, 0x2, 0x194, 0x193, 0x3, 0x2, 0x2, 0x2, 0x195, 
       0x197, 0x3, 0x2, 0x2, 0x2, 0x196, 0x198, 0x5, 0x1c, 0xf, 0x2, 0x197, 
       0x196, 0x3, 0x2, 0x2, 0x2, 0x197, 0x198, 0x3, 0x2, 0x2, 0x2, 0x198, 
       0x19a, 0x3, 0x2, 0x2, 0x2, 0x199, 0x190, 0x3, 0x2, 0x2, 0x2, 0x19a, 
       0x19d, 0x3, 0x2, 0x2, 0x2, 0x19b, 0x199, 0x3, 0x2, 0x2, 0x2, 0x19b, 
       0x19c, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x19d, 
       0x19b, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x1a6, 0x9, 0x5, 0x2, 0x2, 0x19f, 
       0x1a0, 0x7, 0x67, 0x2, 0x2, 0x1a0, 0x1a3, 0x8, 0xe, 0x1, 0x2, 0x1a1, 
       0x1a3, 0x7, 0x4d, 0x2, 0x2, 0x1a2, 0x19f, 0x3, 0x2, 0x2, 0x2, 0x1a2, 
       0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1a4, 
       0x1a7, 0x7, 0x1e, 0x2, 0x2, 0x1a5, 0x1a7, 0x7, 0x26, 0x2, 0x2, 0x1a6, 
       0x1a2, 0x3, 0x2, 0x2, 0x2, 0x1a6, 0x1a4, 0x3, 0x2, 0x2, 0x2, 0x1a6, 
       0x1a5, 0x3, 0x2, 0x2, 0x2, 0x1a7, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1a8, 
       0x1a9, 0x7, 0x39, 0x2, 0x2, 0x1a9, 0x1aa, 0x5, 0xe, 0x8, 0x2, 0x1aa, 
       0x1ab, 0x7, 0x3a, 0x2, 0x2, 0x1ab, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x1ac, 
       0x1b1, 0x5, 0xe, 0x8, 0x2, 0x1ad, 0x1ae, 0x7, 0x5e, 0x2, 0x2, 0x1ae, 
       0x1b0, 0x5, 0xe, 0x8, 0x2, 0x1af, 0x1ad, 0x3, 0x2, 0x2, 0x2, 0x1b0, 
       0x1b3, 0x3, 0x2, 0x2, 0x2, 0x1b1, 0x1af, 0x3, 0x2, 0x2, 0x2, 0x1b1, 
       0x1b2, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x1b3, 
       0x1b1, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b5, 0x7, 0x1a, 0x2, 0x2, 0x1b5, 
       0x1b6, 0x7, 0x67, 0x2, 0x2, 0x1b6, 0x1c3, 0x8, 0x11, 0x1, 0x2, 0x1b7, 
       0x1c0, 0x7, 0x37, 0x2, 0x2, 0x1b8, 0x1bd, 0x5, 0x22, 0x12, 0x2, 0x1b9, 
       0x1ba, 0x7, 0x5e, 0x2, 0x2, 0x1ba, 0x1bc, 0x5, 0x22, 0x12, 0x2, 0x1bb, 
       0x1b9, 0x3, 0x2, 0x2, 0x2, 0x1bc, 0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1bd, 
       0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1bd, 0x1be, 0x3, 0x2, 0x2, 0x2, 0x1be, 
       0x1c1, 0x3, 0x2, 0x2, 0x2, 0x1bf, 0x1bd, 0x3, 0x2, 0x2, 0x2, 0x1c0, 
       0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x1c1, 0x3, 0x2, 0x2, 0x2, 0x1c1, 
       0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c2, 0x1c4, 0x7, 0x38, 0x2, 0x2, 0x1c3, 
       0x1b7, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c4, 0x3, 0x2, 0x2, 0x2, 0x1c4, 
       0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x1c6, 0x7, 0x3b, 0x2, 0x2, 0x1c6, 
       0x1c7, 0x7, 0x72, 0x2, 0x2, 0x1c7, 0x1c8, 0x5, 0x24, 0x13, 0x2, 0x1c8, 
       0x1c9, 0x7, 0x3c, 0x2, 0x2, 0x1c9, 0x1ca, 0x7, 0x72, 0x2, 0x2, 0x1ca, 
       0x21, 0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1cd, 0x7, 0x51, 0x2, 0x2, 0x1cc, 
       0x1cb, 0x3, 0x2, 0x2, 0x2, 0x1cc, 0x1cd, 0x3, 0x2, 0x2, 0x2, 0x1cd, 
       0x1ce, 0x3, 0x2, 0x2, 0x2, 0x1ce, 0x1cf, 0x7, 0x49, 0x2, 0x2, 0x1cf, 
       0x1d0, 0x7, 0x67, 0x2, 0x2, 0x1d0, 0x23, 0x3, 0x2, 0x2, 0x2, 0x1d1, 
       0x1dc, 0x5, 0x26, 0x14, 0x2, 0x1d2, 0x1d4, 0x7, 0x72, 0x2, 0x2, 0x1d3, 
       0x1d2, 0x3, 0x2, 0x2, 0x2, 0x1d3, 0x1d4, 0x3, 0x2, 0x2, 0x2, 0x1d4, 
       0x1d5, 0x3, 0x2, 0x2, 0x2, 0x1d5, 0x1d7, 0x7, 0x41, 0x2, 0x2, 0x1d6, 
       0x1d8, 0x7, 0x72, 0x2, 0x2, 0x1d7, 0x1d6, 0x3, 0x2, 0x2, 0x2, 0x1d7, 
       0x1d8, 0x3, 0x2, 0x2, 0x2, 0x1d8, 0x1d9, 0x3, 0x2, 0x2, 0x2, 0x1d9, 
       0x1db, 0x5, 0x26, 0x14, 0x2, 0x1da, 0x1d3, 0x3, 0x2, 0x2, 0x2, 0x1db, 
       0x1de, 0x3, 0x2, 0x2, 0x2, 0x1dc, 0x1da, 0x3, 0x2, 0x2, 0x2, 0x1dc, 
       0x1dd, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1e0, 0x3, 0x2, 0x2, 0x2, 0x1de, 
       0x1dc, 0x3, 0x2, 0x2, 0x2, 0x1df, 0x1e1, 0x7, 0x72, 0x2, 0x2, 0x1e0, 
       0x1df, 0x3, 0x2, 0x2, 0x2, 0x1e0, 0x1e1, 0x3, 0x2, 0x2, 0x2, 0x1e1, 
       0x25, 0x3, 0x2, 0x2, 0x2, 0x1e2, 0x1ed, 0x5, 0x28, 0x15, 0x2, 0x1e3, 
       0x1e5, 0x7, 0x72, 0x2, 0x2, 0x1e4, 0x1e3, 0x3, 0x2, 0x2, 0x2, 0x1e4, 
       0x1e5, 0x3, 0x2, 0x2, 0x2, 0x1e5, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x1e6, 
       0x1e8, 0x7, 0x40, 0x2, 0x2, 0x1e7, 0x1e9, 0x7, 0x72, 0x2, 0x2, 0x1e8, 
       0x1e7, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1e9, 0x3, 0x2, 0x2, 0x2, 0x1e9, 
       0x1ea, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1ec, 0x5, 0x28, 0x15, 0x2, 0x1eb, 
       0x1e4, 0x3, 0x2, 0x2, 0x2, 0x1ec, 0x1ef, 0x3, 0x2, 0x2, 0x2, 0x1ed, 
       0x1eb, 0x3, 0x2, 0x2, 0x2, 0x1ed, 0x1ee, 0x3, 0x2, 0x2, 0x2, 0x1ee, 
       0x1f1, 0x3, 0x2, 0x2, 0x2, 0x1ef, 0x1ed, 0x3, 0x2, 0x2, 0x2, 0x1f0, 
       0x1f2, 0x7, 0x72, 0x2, 0x2, 0x1f1, 0x1f0, 0x3, 0x2, 0x2, 0x2, 0x1f1, 
       0x1f2, 0x3, 0x2, 0x2, 0x2, 0x1f2, 0x27, 0x3, 0x2, 0x2, 0x2, 0x1f3, 
       0x1fe, 0x5, 0x2a, 0x16, 0x2, 0x1f4, 0x1f6, 0x7, 0x72, 0x2, 0x2, 0x1f5, 
       0x1f4, 0x3, 0x2, 0x2, 0x2, 0x1f5, 0x1f6, 0x3, 0x2, 0x2, 0x2, 0x1f6, 
       0x1f7, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1f9, 0x9, 0x2, 0x2, 0x2, 0x1f8, 
       0x1fa, 0x7, 0x72, 0x2, 0x2, 0x1f9, 0x1f8, 0x3, 0x2, 0x2, 0x2, 0x1f9, 
       0x1fa, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fb, 0x3, 0x2, 0x2, 0x2, 0x1fb, 
       0x1fd, 0x5, 0x2a, 0x16, 0x2, 0x1fc, 0x1f5, 0x3, 0x2, 0x2, 0x2, 0x1fd, 
       0x200, 0x3, 0x2, 0x2, 0x2, 0x1fe, 0x1fc, 0x3, 0x2, 0x2, 0x2, 0x1fe, 
       0x1ff, 0x3, 0x2, 0x2, 0x2, 0x1ff, 0x202, 0x3, 0x2, 0x2, 0x2, 0x200, 
       0x1fe, 0x3, 0x2, 0x2, 0x2, 0x201, 0x203, 0x7, 0x72, 0x2, 0x2, 0x202, 
       0x201, 0x3, 0x2, 0x2, 0x2, 0x202, 0x203, 0x3, 0x2, 0x2, 0x2, 0x203, 
       0x29, 0x3, 0x2, 0x2, 0x2, 0x204, 0x20f, 0x5, 0x2c, 0x17, 0x2, 0x205, 
       0x207, 0x7, 0x72, 0x2, 0x2, 0x206, 0x205, 0x3, 0x2, 0x2, 0x2, 0x206, 
       0x207, 0x3, 0x2, 0x2, 0x2, 0x207, 0x208, 0x3, 0x2, 0x2, 0x2, 0x208, 
       0x20a, 0x9, 0x3, 0x2, 0x2, 0x209, 0x20b, 0x7, 0x72, 0x2, 0x2, 0x20a, 
       0x209, 0x3, 0x2, 0x2, 0x2, 0x20a, 0x20b, 0x3, 0x2, 0x2, 0x2, 0x20b, 
       0x20c, 0x3, 0x2, 0x2, 0x2, 0x20c, 0x20e, 0x5, 0x2c, 0x17, 0x2, 0x20d, 
       0x206, 0x3, 0x2, 0x2, 0x2, 0x20e, 0x211, 0x3, 0x2, 0x2, 0x2, 0x20f, 
       0x20d, 0x3, 0x2, 0x2, 0x2, 0x20f, 0x210, 0x3, 0x2, 0x2, 0x2, 0x210, 
       0x213, 0x3, 0x2, 0x2, 0x2, 0x211, 0x20f, 0x3, 0x2, 0x2, 0x2, 0x212, 
       0x214, 0x7, 0x72, 0x2, 0x2, 0x213, 0x212, 0x3, 0x2, 0x2, 0x2, 0x213, 
       0x214, 0x3, 0x2, 0x2, 0x2, 0x214, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x215, 
       0x220, 0x5, 0x2e, 0x18, 0x2, 0x216, 0x218, 0x7, 0x72, 0x2, 0x2, 0x217, 
       0x216, 0x3, 0x2, 0x2, 0x2, 0x217, 0x218, 0x3, 0x2, 0x2, 0x2, 0x218, 
       0x219, 0x3, 0x2, 0x2, 0x2, 0x219, 0x21b, 0x9, 0x4, 0x2, 0x2, 0x21a, 
       0x21c, 0x7, 0x72, 0x2, 0x2, 0x21b, 0x21a, 0x3, 0x2, 0x2, 0x2, 0x21b, 
       0x21c, 0x3, 0x2, 0x2, 0x2, 0x21c, 0x21d, 0x3, 0x2, 0x2, 0x2, 0x21d, 
       0x21f, 0x5, 0x2e, 0x18, 0x2, 0x21e, 0x217, 0x3, 0x2, 0x2, 0x2, 0x21f, 
       0x222, 0x3, 0x2, 0x2, 0x2, 0x220, 0x21e, 0x3, 0x2, 0x2, 0x2, 0x220, 
       0x221, 0x3, 0x2, 0x2, 0x2, 0x221, 0x224, 0x3, 0x2, 0x2, 0x2, 0x222, 
       0x220, 0x3, 0x2, 0x2, 0x2, 0x223, 0x225, 0x7, 0x72, 0x2, 0x2, 0x224, 
       0x223, 0x3, 0x2, 0x2, 0x2, 0x224, 0x225, 0x3, 0x2, 0x2, 0x2, 0x225, 
       0x2d, 0x3, 0x2, 0x2, 0x2, 0x226, 0x254, 0x7, 0x8, 0x2, 0x2, 0x227, 
       0x254, 0x7, 0x6, 0x2, 0x2, 0x228, 0x254, 0x7, 0x9, 0x2, 0x2, 0x229, 
       0x254, 0x7, 0x5, 0x2, 0x2, 0x22a, 0x254, 0x7, 0x7, 0x2, 0x2, 0x22b, 
       0x254, 0x7, 0x1e, 0x2, 0x2, 0x22c, 0x22d, 0x7, 0x42, 0x2, 0x2, 0x22d, 
       0x254, 0x7, 0x67, 0x2, 0x2, 0x22e, 0x254, 0x7, 0x26, 0x2, 0x2, 0x22f, 
       0x231, 0x7, 0x37, 0x2, 0x2, 0x230, 0x232, 0x7, 0x72, 0x2, 0x2, 0x231, 
       0x230, 0x3, 0x2, 0x2, 0x2, 0x231, 0x232, 0x3, 0x2, 0x2, 0x2, 0x232, 
       0x233, 0x3, 0x2, 0x2, 0x2, 0x233, 0x235, 0x5, 0x24, 0x13, 0x2, 0x234, 
       0x236, 0x7, 0x72, 0x2, 0x2, 0x235, 0x234, 0x3, 0x2, 0x2, 0x2, 0x235, 
       0x236, 0x3, 0x2, 0x2, 0x2, 0x236, 0x237, 0x3, 0x2, 0x2, 0x2, 0x237, 
       0x239, 0x7, 0x38, 0x2, 0x2, 0x238, 0x23a, 0x7, 0x72, 0x2, 0x2, 0x239, 
       0x238, 0x3, 0x2, 0x2, 0x2, 0x239, 0x23a, 0x3, 0x2, 0x2, 0x2, 0x23a, 
       0x254, 0x3, 0x2, 0x2, 0x2, 0x23b, 0x23d, 0x7, 0x67, 0x2, 0x2, 0x23c, 
       0x23e, 0x7, 0x72, 0x2, 0x2, 0x23d, 0x23c, 0x3, 0x2, 0x2, 0x2, 0x23d, 
       0x23e, 0x3, 0x2, 0x2, 0x2, 0x23e, 0x23f, 0x3, 0x2, 0x2, 0x2, 0x23f, 
       0x241, 0x7, 0x37, 0x2, 0x2, 0x240, 0x242, 0x7, 0x72, 0x2, 0x2, 0x241, 
       0x240, 0x3, 0x2, 0x2, 0x2, 0x241, 0x242, 0x3, 0x2, 0x2, 0x2, 0x242, 
       0x244, 0x3, 0x2, 0x2, 0x2, 0x243, 0x245, 0x5, 0x34, 0x1b, 0x2, 0x244, 
       0x243, 0x3, 0x2, 0x2, 0x2, 0x244, 0x245, 0x3, 0x2, 0x2, 0x2, 0x245, 
       0x247, 0x3, 0x2, 0x2, 0x2, 0x246, 0x248, 0x7, 0x72, 0x2, 0x2, 0x247, 
       0x246, 0x3, 0x2, 0x2, 0x2, 0x247, 0x248, 0x3, 0x2, 0x2, 0x2, 0x248, 
       0x249, 0x3, 0x2, 0x2, 0x2, 0x249, 0x24b, 0x7, 0x38, 0x2, 0x2, 0x24a, 
       0x24c, 0x7, 0x72, 0x2, 0x2, 0x24b, 0x24a, 0x3, 0x2, 0x2, 0x2, 0x24b, 
       0x24c, 0x3, 0x2, 0x2, 0x2, 0x24c, 0x254, 0x3, 0x2, 0x2, 0x2, 0x24d, 
       0x24f, 0x5, 0x30, 0x19, 0x2, 0x24e, 0x250, 0x7, 0x72, 0x2, 0x2, 0x24f, 
       0x24e, 0x3, 0x2, 0x2, 0x2, 0x24f, 0x250, 0x3, 0x2, 0x2, 0x2, 0x250, 
       0x254, 0x3, 0x2, 0x2, 0x2, 0x251, 0x252, 0x7, 0x49, 0x2, 0x2, 0x252, 
       0x254, 0x7, 0x67, 0x2, 0x2, 0x253, 0x226, 0x3, 0x2, 0x2, 0x2, 0x253, 
       0x227, 0x3, 0x2, 0x2, 0x2, 0x253, 0x228, 0x3, 0x2, 0x2, 0x2, 0x253, 
       0x229, 0x3, 0x2, 0x2, 0x2, 0x253, 0x22a, 0x3, 0x2, 0x2, 0x2, 0x253, 
       0x22b, 0x3, 0x2, 0x2, 0x2, 0x253, 0x22c, 0x3, 0x2, 0x2, 0x2, 0x253, 
       0x22e, 0x3, 0x2, 0x2, 0x2, 0x253, 0x22f, 0x3, 0x2, 0x2, 0x2, 0x253, 
       0x23b, 0x3, 0x2, 0x2, 0x2, 0x253, 0x24d, 0x3, 0x2, 0x2, 0x2, 0x253, 
       0x251, 0x3, 0x2, 0x2, 0x2, 0x254, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x255, 
       0x257, 0x9, 0x5, 0x2, 0x2, 0x256, 0x255, 0x3, 0x2, 0x2, 0x2, 0x256, 
       0x257, 0x3, 0x2, 0x2, 0x2, 0x257, 0x259, 0x3, 0x2, 0x2, 0x2, 0x258, 
       0x25a, 0x7, 0x72, 0x2, 0x2, 0x259, 0x258, 0x3, 0x2, 0x2, 0x2, 0x259, 
       0x25a, 0x3, 0x2, 0x2, 0x2, 0x25a, 0x25b, 0x3, 0x2, 0x2, 0x2, 0x25b, 
       0x25d, 0x9, 0x6, 0x2, 0x2, 0x25c, 0x25e, 0x7, 0x72, 0x2, 0x2, 0x25d, 
       0x25c, 0x3, 0x2, 0x2, 0x2, 0x25d, 0x25e, 0x3, 0x2, 0x2, 0x2, 0x25e, 
       0x260, 0x3, 0x2, 0x2, 0x2, 0x25f, 0x261, 0x5, 0x32, 0x1a, 0x2, 0x260, 
       0x25f, 0x3, 0x2, 0x2, 0x2, 0x260, 0x261, 0x3, 0x2, 0x2, 0x2, 0x261, 
       0x26f, 0x3, 0x2, 0x2, 0x2, 0x262, 0x264, 0x9, 0x5, 0x2, 0x2, 0x263, 
       0x265, 0x7, 0x72, 0x2, 0x2, 0x264, 0x263, 0x3, 0x2, 0x2, 0x2, 0x264, 
       0x265, 0x3, 0x2, 0x2, 0x2, 0x265, 0x266, 0x3, 0x2, 0x2, 0x2, 0x266, 
       0x268, 0x9, 0x6, 0x2, 0x2, 0x267, 0x269, 0x7, 0x72, 0x2, 0x2, 0x268, 
       0x267, 0x3, 0x2, 0x2, 0x2, 0x268, 0x269, 0x3, 0x2, 0x2, 0x2, 0x269, 
       0x26b, 0x3, 0x2, 0x2, 0x2, 0x26a, 0x26c, 0x5, 0x32, 0x1a, 0x2, 0x26b, 
       0x26a, 0x3, 0x2, 0x2, 0x2, 0x26b, 0x26c, 0x3, 0x2, 0x2, 0x2, 0x26c, 
       0x26e, 0x3, 0x2, 0x2, 0x2, 0x26d, 0x262, 0x3, 0x2, 0x2, 0x2, 0x26e, 
       0x271, 0x3, 0x2, 0x2, 0x2, 0x26f, 0x26d, 0x3, 0x2, 0x2, 0x2, 0x26f, 
       0x270, 0x3, 0x2, 0x2, 0x2, 0x270, 0x27d, 0x3, 0x2, 0x2, 0x2, 0x271, 
       0x26f, 0x3, 0x2, 0x2, 0x2, 0x272, 0x274, 0x9, 0x5, 0x2, 0x2, 0x273, 
       0x275, 0x7, 0x72, 0x2, 0x2, 0x274, 0x273, 0x3, 0x2, 0x2, 0x2, 0x274, 
       0x275, 0x3, 0x2, 0x2, 0x2, 0x275, 0x27b, 0x3, 0x2, 0x2, 0x2, 0x276, 
       0x27c, 0x9, 0x6, 0x2, 0x2, 0x277, 0x27c, 0x7, 0x1e, 0x2, 0x2, 0x278, 
       0x279, 0x7, 0x42, 0x2, 0x2, 0x279, 0x27c, 0x7, 0x67, 0x2, 0x2, 0x27a, 
       0x27c, 0x7, 0x26, 0x2, 0x2, 0x27b, 0x276, 0x3, 0x2, 0x2, 0x2, 0x27b, 
       0x277, 0x3, 0x2, 0x2, 0x2, 0x27b, 0x278, 0x3, 0x2, 0x2, 0x2, 0x27b, 
       0x27a, 0x3, 0x2, 0x2, 0x2, 0x27c, 0x27e, 0x3, 0x2, 0x2, 0x2, 0x27d, 
       0x272, 0x3, 0x2, 0x2, 0x2, 0x27d, 0x27e, 0x3, 0x2, 0x2, 0x2, 0x27e, 
       0x31, 0x3, 0x2, 0x2, 0x2, 0x27f, 0x281, 0x7, 0x39, 0x2, 0x2, 0x280, 
       0x282, 0x7, 0x72, 0x2, 0x2, 0x281, 0x280, 0x3, 0x2, 0x2, 0x2, 0x281, 
       0x282, 0x3, 0x2, 0x2, 0x2, 0x282, 0x283, 0x3, 0x2, 0x2, 0x2, 0x283, 
       0x285, 0x5, 0x24, 0x13, 0x2, 0x284, 0x286, 0x7, 0x72, 0x2, 0x2, 0x285, 
       0x284, 0x3, 0x2, 0x2, 0x2, 0x285, 0x286, 0x3, 0x2, 0x2, 0x2, 0x286, 
       0x287, 0x3, 0x2, 0x2, 0x2, 0x287, 0x288, 0x7, 0x3a, 0x2, 0x2, 0x288, 
       0x33, 0x3, 0x2, 0x2, 0x2, 0x289, 0x294, 0x5, 0x24, 0x13, 0x2, 0x28a, 
       0x28c, 0x7, 0x72, 0x2, 0x2, 0x28b, 0x28a, 0x3, 0x2, 0x2, 0x2, 0x28b, 
       0x28c, 0x3, 0x2, 0x2, 0x2, 0x28c, 0x28d, 0x3, 0x2, 0x2, 0x2, 0x28d, 
       0x28f, 0x7, 0x5e, 0x2, 0x2, 0x28e, 0x290, 0x7, 0x72, 0x2, 0x2, 0x28f, 
       0x28e, 0x3, 0x2, 0x2, 0x2, 0x28f, 0x290, 0x3, 0x2, 0x2, 0x2, 0x290, 
       0x291, 0x3, 0x2, 0x2, 0x2, 0x291, 0x293, 0x5, 0x24, 0x13, 0x2, 0x292, 
       0x28b, 0x3, 0x2, 0x2, 0x2, 0x293, 0x296, 0x3, 0x2, 0x2, 0x2, 0x294, 
       0x292, 0x3, 0x2, 0x2, 0x2, 0x294, 0x295, 0x3, 0x2, 0x2, 0x2, 0x295, 
       0x298, 0x3, 0x2, 0x2, 0x2, 0x296, 0x294, 0x3, 0x2, 0x2, 0x2, 0x297, 
       0x299, 0x7, 0x72, 0x2, 0x2, 0x298, 0x297, 0x3, 0x2, 0x2, 0x2, 0x298, 
       0x299, 0x3, 0x2, 0x2, 0x2, 0x299, 0x35, 0x3, 0x2, 0x2, 0x2, 0x29a, 
       0x29b, 0x7, 0x3b, 0x2, 0x2, 0x29b, 0x29f, 0x7, 0x72, 0x2, 0x2, 0x29c, 
       0x29e, 0x5, 0x38, 0x1d, 0x2, 0x29d, 0x29c, 0x3, 0x2, 0x2, 0x2, 0x29e, 
       0x2a1, 0x3, 0x2, 0x2, 0x2, 0x29f, 0x29d, 0x3, 0x2, 0x2, 0x2, 0x29f, 
       0x2a0, 0x3, 0x2, 0x2, 0x2, 0x2a0, 0x2ac, 0x3, 0x2, 0x2, 0x2, 0x2a1, 
       0x29f, 0x3, 0x2, 0x2, 0x2, 0x2a2, 0x2a3, 0x7, 0x2d, 0x2, 0x2, 0x2a3, 
       0x2a7, 0x7, 0x72, 0x2, 0x2, 0x2a4, 0x2a6, 0x5, 0x38, 0x1d, 0x2, 0x2a5, 
       0x2a4, 0x3, 0x2, 0x2, 0x2, 0x2a6, 0x2a9, 0x3, 0x2, 0x2, 0x2, 0x2a7, 
       0x2a5, 0x3, 0x2, 0x2, 0x2, 0x2a7, 0x2a8, 0x3, 0x2, 0x2, 0x2, 0x2a8, 
       0x2aa, 0x3, 0x2, 0x2, 0x2, 0x2a9, 0x2a7, 0x3, 0x2, 0x2, 0x2, 0x2aa, 
       0x2ab, 0x7, 0x2e, 0x2, 0x2, 0x2ab, 0x2ad, 0x7, 0x72, 0x2, 0x2, 0x2ac, 
       0x2a2, 0x3, 0x2, 0x2, 0x2, 0x2ac, 0x2ad, 0x3, 0x2, 0x2, 0x2, 0x2ad, 
       0x2b1, 0x3, 0x2, 0x2, 0x2, 0x2ae, 0x2b0, 0x5, 0x38, 0x1d, 0x2, 0x2af, 
       0x2ae, 0x3, 0x2, 0x2, 0x2, 0x2b0, 0x2b3, 0x3, 0x2, 0x2, 0x2, 0x2b1, 
       0x2af, 0x3, 0x2, 0x2, 0x2, 0x2b1, 0x2b2, 0x3, 0x2, 0x2, 0x2, 0x2b2, 
       0x2b4, 0x3, 0x2, 0x2, 0x2, 0x2b3, 0x2b1, 0x3, 0x2, 0x2, 0x2, 0x2b4, 
       0x2b5, 0x7, 0x3c, 0x2, 0x2, 0x2b5, 0x2b6, 0x7, 0x63, 0x2, 0x2, 0x2b6, 
       0x2b7, 0x7, 0x72, 0x2, 0x2, 0x2b7, 0x37, 0x3, 0x2, 0x2, 0x2, 0x2b8, 
       0x2ba, 0x5, 0x3a, 0x1e, 0x2, 0x2b9, 0x2b8, 0x3, 0x2, 0x2, 0x2, 0x2b9, 
       0x2ba, 0x3, 0x2, 0x2, 0x2, 0x2ba, 0x2bb, 0x3, 0x2, 0x2, 0x2, 0x2bb, 
       0x2bc, 0x7, 0x72, 0x2, 0x2, 0x2bc, 0x39, 0x3, 0x2, 0x2, 0x2, 0x2bd, 
       0x2cc, 0x6, 0x1e, 0x2, 0x2, 0x2be, 0x2c3, 0x7, 0x37, 0x2, 0x2, 0x2bf, 
       0x2c2, 0x5, 0x3a, 0x1e, 0x2, 0x2c0, 0x2c2, 0x7, 0x72, 0x2, 0x2, 0x2c1, 
       0x2bf, 0x3, 0x2, 0x2, 0x2, 0x2c1, 0x2c0, 0x3, 0x2, 0x2, 0x2, 0x2c2, 
       0x2c5, 0x3, 0x2, 0x2, 0x2, 0x2c3, 0x2c1, 0x3, 0x2, 0x2, 0x2, 0x2c3, 
       0x2c4, 0x3, 0x2, 0x2, 0x2, 0x2c4, 0x2c8, 0x3, 0x2, 0x2, 0x2, 0x2c5, 
       0x2c3, 0x3, 0x2, 0x2, 0x2, 0x2c6, 0x2c9, 0x5, 0x3c, 0x1f, 0x2, 0x2c7, 
       0x2c9, 0x7, 0x38, 0x2, 0x2, 0x2c8, 0x2c6, 0x3, 0x2, 0x2, 0x2, 0x2c8, 
       0x2c7, 0x3, 0x2, 0x2, 0x2, 0x2c9, 0x2cd, 0x3, 0x2, 0x2, 0x2, 0x2ca, 
       0x2cd, 0x7, 0x4, 0x2, 0x2, 0x2cb, 0x2cd, 0x7, 0x3, 0x2, 0x2, 0x2cc, 
       0x2be, 0x3, 0x2, 0x2, 0x2, 0x2cc, 0x2ca, 0x3, 0x2, 0x2, 0x2, 0x2cc, 
       0x2cb, 0x3, 0x2, 0x2, 0x2, 0x2cd, 0x2cf, 0x3, 0x2, 0x2, 0x2, 0x2ce, 
       0x2d0, 0x5, 0x3a, 0x1e, 0x2, 0x2cf, 0x2ce, 0x3, 0x2, 0x2, 0x2, 0x2cf, 
       0x2d0, 0x3, 0x2, 0x2, 0x2, 0x2d0, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x2d1, 
       0x2d6, 0x5, 0x3e, 0x20, 0x2, 0x2d2, 0x2d6, 0x5, 0x40, 0x21, 0x2, 
       0x2d3, 0x2d6, 0x5, 0x42, 0x22, 0x2, 0x2d4, 0x2d6, 0x5, 0x44, 0x23, 
       0x2, 0x2d5, 0x2d1, 0x3, 0x2, 0x2, 0x2, 0x2d5, 0x2d2, 0x3, 0x2, 0x2, 
       0x2, 0x2d5, 0x2d3, 0x3, 0x2, 0x2, 0x2, 0x2d5, 0x2d4, 0x3, 0x2, 0x2, 
       0x2, 0x2d6, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x2d7, 0x2d8, 0x7, 0x33, 0x2, 
       0x2, 0x2d8, 0x2e3, 0x7, 0x67, 0x2, 0x2, 0x2d9, 0x2da, 0x7, 0x64, 
       0x2, 0x2, 0x2da, 0x2db, 0x7, 0x67, 0x2, 0x2, 0x2db, 0x2dc, 0x7, 0x3b, 
       0x2, 0x2, 0x2dc, 0x2dd, 0x7, 0x67, 0x2, 0x2, 0x2dd, 0x2de, 0x7, 0x3c, 
       0x2, 0x2, 0x2de, 0x2df, 0x7, 0x3c, 0x2, 0x2, 0x2df, 0x2e4, 0x8, 0x20, 
       0x1, 0x2, 0x2e0, 0x2e1, 0x7, 0x3c, 0x2, 0x2, 0x2e1, 0x2e4, 0x8, 0x20, 
       0x1, 0x2, 0x2e2, 0x2e4, 0x8, 0x20, 0x1, 0x2, 0x2e3, 0x2d9, 0x3, 0x2, 
       0x2, 0x2, 0x2e3, 0x2e0, 0x3, 0x2, 0x2, 0x2, 0x2e3, 0x2e2, 0x3, 0x2, 
       0x2, 0x2, 0x2e4, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x2e5, 0x2e8, 0x7, 0x34, 
       0x2, 0x2, 0x2e6, 0x2e9, 0x7, 0x67, 0x2, 0x2, 0x2e7, 0x2e9, 0x8, 0x21, 
       0x1, 0x2, 0x2e8, 0x2e6, 0x3, 0x2, 0x2, 0x2, 0x2e8, 0x2e7, 0x3, 0x2, 
       0x2, 0x2, 0x2e9, 0x2ea, 0x3, 0x2, 0x2, 0x2, 0x2ea, 0x2eb, 0x7, 0x3c, 
       0x2, 0x2, 0x2eb, 0x2ec, 0x8, 0x21, 0x1, 0x2, 0x2ec, 0x41, 0x3, 0x2, 
       0x2, 0x2, 0x2ed, 0x2f0, 0x7, 0x35, 0x2, 0x2, 0x2ee, 0x2f1, 0x7, 0x67, 
       0x2, 0x2, 0x2ef, 0x2f1, 0x8, 0x22, 0x1, 0x2, 0x2f0, 0x2ee, 0x3, 0x2, 
       0x2, 0x2, 0x2f0, 0x2ef, 0x3, 0x2, 0x2, 0x2, 0x2f1, 0x2f2, 0x3, 0x2, 
       0x2, 0x2, 0x2f2, 0x2f3, 0x7, 0x3c, 0x2, 0x2, 0x2f3, 0x2f4, 0x8, 0x22, 
       0x1, 0x2, 0x2f4, 0x43, 0x3, 0x2, 0x2, 0x2, 0x2f5, 0x2f8, 0x7, 0x36, 
       0x2, 0x2, 0x2f6, 0x2f9, 0x5, 0x46, 0x24, 0x2, 0x2f7, 0x2f9, 0x8, 
       0x23, 0x1, 0x2, 0x2f8, 0x2f6, 0x3, 0x2, 0x2, 0x2, 0x2f8, 0x2f7, 0x3, 
       0x2, 0x2, 0x2, 0x2f9, 0x2fa, 0x3, 0x2, 0x2, 0x2, 0x2fa, 0x2fb, 0x7, 
       0x3c, 0x2, 0x2, 0x2fb, 0x45, 0x3, 0x2, 0x2, 0x2, 0x2fc, 0x2fe, 0x7, 
       0x72, 0x2, 0x2, 0x2fd, 0x2fc, 0x3, 0x2, 0x2, 0x2, 0x2fd, 0x2fe, 0x3, 
       0x2, 0x2, 0x2, 0x2fe, 0x2ff, 0x3, 0x2, 0x2, 0x2, 0x2ff, 0x30a, 0x5, 
       0x48, 0x25, 0x2, 0x300, 0x302, 0x7, 0x72, 0x2, 0x2, 0x301, 0x300, 
       0x3, 0x2, 0x2, 0x2, 0x301, 0x302, 0x3, 0x2, 0x2, 0x2, 0x302, 0x303, 
       0x3, 0x2, 0x2, 0x2, 0x303, 0x305, 0x7, 0x63, 0x2, 0x2, 0x304, 0x306, 
       0x7, 0x72, 0x2, 0x2, 0x305, 0x304, 0x3, 0x2, 0x2, 0x2, 0x305, 0x306, 
       0x3, 0x2, 0x2, 0x2, 0x306, 0x307, 0x3, 0x2, 0x2, 0x2, 0x307, 0x309, 
       0x5, 0x48, 0x25, 0x2, 0x308, 0x301, 0x3, 0x2, 0x2, 0x2, 0x309, 0x30c, 
       0x3, 0x2, 0x2, 0x2, 0x30a, 0x308, 0x3, 0x2, 0x2, 0x2, 0x30a, 0x30b, 
       0x3, 0x2, 0x2, 0x2, 0x30b, 0x30e, 0x3, 0x2, 0x2, 0x2, 0x30c, 0x30a, 
       0x3, 0x2, 0x2, 0x2, 0x30d, 0x30f, 0x7, 0x72, 0x2, 0x2, 0x30e, 0x30d, 
       0x3, 0x2, 0x2, 0x2, 0x30e, 0x30f, 0x3, 0x2, 0x2, 0x2, 0x30f, 0x47, 
       0x3, 0x2, 0x2, 0x2, 0x310, 0x312, 0x7, 0x72, 0x2, 0x2, 0x311, 0x310, 
       0x3, 0x2, 0x2, 0x2, 0x311, 0x312, 0x3, 0x2, 0x2, 0x2, 0x312, 0x313, 
       0x3, 0x2, 0x2, 0x2, 0x313, 0x31e, 0x5, 0x4a, 0x26, 0x2, 0x314, 0x316, 
       0x7, 0x72, 0x2, 0x2, 0x315, 0x314, 0x3, 0x2, 0x2, 0x2, 0x315, 0x316, 
       0x3, 0x2, 0x2, 0x2, 0x316, 0x317, 0x3, 0x2, 0x2, 0x2, 0x317, 0x319, 
       0x7, 0x5e, 0x2, 0x2, 0x318, 0x31a, 0x7, 0x72, 0x2, 0x2, 0x319, 0x318, 
       0x3, 0x2, 0x2, 0x2, 0x319, 0x31a, 0x3, 0x2, 0x2, 0x2, 0x31a, 0x31b, 
       0x3, 0x2, 0x2, 0x2, 0x31b, 0x31d, 0x5, 0x4a, 0x26, 0x2, 0x31c, 0x315, 
       0x3, 0x2, 0x2, 0x2, 0x31d, 0x320, 0x3, 0x2, 0x2, 0x2, 0x31e, 0x31c, 
       0x3, 0x2, 0x2, 0x2, 0x31e, 0x31f, 0x3, 0x2, 0x2, 0x2, 0x31f, 0x322, 
       0x3, 0x2, 0x2, 0x2, 0x320, 0x31e, 0x3, 0x2, 0x2, 0x2, 0x321, 0x323, 
       0x7, 0x72, 0x2, 0x2, 0x322, 0x321, 0x3, 0x2, 0x2, 0x2, 0x322, 0x323, 
       0x3, 0x2, 0x2, 0x2, 0x323, 0x49, 0x3, 0x2, 0x2, 0x2, 0x324, 0x326, 
       0x7, 0x72, 0x2, 0x2, 0x325, 0x324, 0x3, 0x2, 0x2, 0x2, 0x325, 0x326, 
       0x3, 0x2, 0x2, 0x2, 0x326, 0x327, 0x3, 0x2, 0x2, 0x2, 0x327, 0x329, 
       0x7, 0x37, 0x2, 0x2, 0x328, 0x32a, 0x7, 0x72, 0x2, 0x2, 0x329, 0x328, 
       0x3, 0x2, 0x2, 0x2, 0x329, 0x32a, 0x3, 0x2, 0x2, 0x2, 0x32a, 0x32b, 
       0x3, 0x2, 0x2, 0x2, 0x32b, 0x32d, 0x5, 0x46, 0x24, 0x2, 0x32c, 0x32e, 
       0x7, 0x72, 0x2, 0x2, 0x32d, 0x32c, 0x3, 0x2, 0x2, 0x2, 0x32d, 0x32e, 
       0x3, 0x2, 0x2, 0x2, 0x32e, 0x32f, 0x3, 0x2, 0x2, 0x2, 0x32f, 0x331, 
       0x7, 0x38, 0x2, 0x2, 0x330, 0x332, 0x7, 0x72, 0x2, 0x2, 0x331, 0x330, 
       0x3, 0x2, 0x2, 0x2, 0x331, 0x332, 0x3, 0x2, 0x2, 0x2, 0x332, 0x33b, 
       0x3, 0x2, 0x2, 0x2, 0x333, 0x335, 0x7, 0x72, 0x2, 0x2, 0x334, 0x333, 
       0x3, 0x2, 0x2, 0x2, 0x334, 0x335, 0x3, 0x2, 0x2, 0x2, 0x335, 0x336, 
       0x3, 0x2, 0x2, 0x2, 0x336, 0x338, 0x5, 0x4c, 0x27, 0x2, 0x337, 0x339, 
       0x7, 0x72, 0x2, 0x2, 0x338, 0x337, 0x3, 0x2, 0x2, 0x2, 0x338, 0x339, 
       0x3, 0x2, 0x2, 0x2, 0x339, 0x33b, 0x3, 0x2, 0x2, 0x2, 0x33a, 0x325, 
       0x3, 0x2, 0x2, 0x2, 0x33a, 0x334, 0x3, 0x2, 0x2, 0x2, 0x33b, 0x4b, 
       0x3, 0x2, 0x2, 0x2, 0x33c, 0x361, 0x5, 0x50, 0x29, 0x2, 0x33d, 0x361, 
       0x7, 0x30, 0x2, 0x2, 0x33e, 0x340, 0x7, 0x54, 0x2, 0x2, 0x33f, 0x33e, 
       0x3, 0x2, 0x2, 0x2, 0x33f, 0x340, 0x3, 0x2, 0x2, 0x2, 0x340, 0x341, 
       0x3, 0x2, 0x2, 0x2, 0x341, 0x344, 0x7, 0x67, 0x2, 0x2, 0x342, 0x343, 
       0x7, 0x64, 0x2, 0x2, 0x343, 0x345, 0x7, 0x67, 0x2, 0x2, 0x344, 0x342, 
       0x3, 0x2, 0x2, 0x2, 0x344, 0x345, 0x3, 0x2, 0x2, 0x2, 0x345, 0x35e, 
       0x3, 0x2, 0x2, 0x2, 0x346, 0x358, 0x7, 0x37, 0x2, 0x2, 0x347, 0x349, 
       0x7, 0x72, 0x2, 0x2, 0x348, 0x347, 0x3, 0x2, 0x2, 0x2, 0x348, 0x349, 
       0x3, 0x2, 0x2, 0x2, 0x349, 0x34a, 0x3, 0x2, 0x2, 0x2, 0x34a, 0x355, 
       0x5, 0x4e, 0x28, 0x2, 0x34b, 0x34d, 0x7, 0x72, 0x2, 0x2, 0x34c, 0x34b, 
       0x3, 0x2, 0x2, 0x2, 0x34c, 0x34d, 0x3, 0x2, 0x2, 0x2, 0x34d, 0x34e, 
       0x3, 0x2, 0x2, 0x2, 0x34e, 0x350, 0x7, 0x5e, 0x2, 0x2, 0x34f, 0x351, 
       0x7, 0x72, 0x2, 0x2, 0x350, 0x34f, 0x3, 0x2, 0x2, 0x2, 0x350, 0x351, 
       0x3, 0x2, 0x2, 0x2, 0x351, 0x352, 0x3, 0x2, 0x2, 0x2, 0x352, 0x354, 
       0x5, 0x4e, 0x28, 0x2, 0x353, 0x34c, 0x3, 0x2, 0x2, 0x2, 0x354, 0x357, 
       0x3, 0x2, 0x2, 0x2, 0x355, 0x353, 0x3, 0x2, 0x2, 0x2, 0x355, 0x356, 
       0x3, 0x2, 0x2, 0x2, 0x356, 0x359, 0x3, 0x2, 0x2, 0x2, 0x357, 0x355, 
       0x3, 0x2, 0x2, 0x2, 0x358, 0x348, 0x3, 0x2, 0x2, 0x2, 0x358, 0x359, 
       0x3, 0x2, 0x2, 0x2, 0x359, 0x35b, 0x3, 0x2, 0x2, 0x2, 0x35a, 0x35c, 
       0x7, 0x72, 0x2, 0x2, 0x35b, 0x35a, 0x3, 0x2, 0x2, 0x2, 0x35b, 0x35c, 
       0x3, 0x2, 0x2, 0x2, 0x35c, 0x35d, 0x3, 0x2, 0x2, 0x2, 0x35d, 0x35f, 
       0x7, 0x38, 0x2, 0x2, 0x35e, 0x346, 0x3, 0x2, 0x2, 0x2, 0x35e, 0x35f, 
       0x3, 0x2, 0x2, 0x2, 0x35f, 0x361, 0x3, 0x2, 0x2, 0x2, 0x360, 0x33c, 
       0x3, 0x2, 0x2, 0x2, 0x360, 0x33d, 0x3, 0x2, 0x2, 0x2, 0x360, 0x33f, 
       0x3, 0x2, 0x2, 0x2, 0x361, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x362, 0x370, 
       0x7, 0x4a, 0x2, 0x2, 0x363, 0x366, 0x7, 0x49, 0x2, 0x2, 0x364, 0x365, 
       0x7, 0x67, 0x2, 0x2, 0x365, 0x367, 0x8, 0x28, 0x1, 0x2, 0x366, 0x364, 
       0x3, 0x2, 0x2, 0x2, 0x366, 0x367, 0x3, 0x2, 0x2, 0x2, 0x367, 0x370, 
       0x3, 0x2, 0x2, 0x2, 0x368, 0x370, 0x7, 0x8, 0x2, 0x2, 0x369, 0x370, 
       0x7, 0x6, 0x2, 0x2, 0x36a, 0x370, 0x7, 0x9, 0x2, 0x2, 0x36b, 0x370, 
       0x7, 0x5, 0x2, 0x2, 0x36c, 0x370, 0x7, 0x7, 0x2, 0x2, 0x36d, 0x36e, 
       0x7, 0x67, 0x2, 0x2, 0x36e, 0x370, 0x8, 0x28, 0x1, 0x2, 0x36f, 0x362, 
       0x3, 0x2, 0x2, 0x2, 0x36f, 0x363, 0x3, 0x2, 0x2, 0x2, 0x36f, 0x368, 
       0x3, 0x2, 0x2, 0x2, 0x36f, 0x369, 0x3, 0x2, 0x2, 0x2, 0x36f, 0x36a, 
       0x3, 0x2, 0x2, 0x2, 0x36f, 0x36b, 0x3, 0x2, 0x2, 0x2, 0x36f, 0x36c, 
       0x3, 0x2, 0x2, 0x2, 0x36f, 0x36d, 0x3, 0x2, 0x2, 0x2, 0x370, 0x4f, 
       0x3, 0x2, 0x2, 0x2, 0x371, 0x373, 0x7, 0x2f, 0x2, 0x2, 0x372, 0x374, 
       0x7, 0x72, 0x2, 0x2, 0x373, 0x372, 0x3, 0x2, 0x2, 0x2, 0x373, 0x374, 
       0x3, 0x2, 0x2, 0x2, 0x374, 0x37e, 0x3, 0x2, 0x2, 0x2, 0x375, 0x377, 
       0x7, 0x37, 0x2, 0x2, 0x376, 0x378, 0x7, 0x72, 0x2, 0x2, 0x377, 0x376, 
       0x3, 0x2, 0x2, 0x2, 0x377, 0x378, 0x3, 0x2, 0x2, 0x2, 0x378, 0x379, 
       0x3, 0x2, 0x2, 0x2, 0x379, 0x37b, 0x7, 0x2c, 0x2, 0x2, 0x37a, 0x37c, 
       0x7, 0x72, 0x2, 0x2, 0x37b, 0x37a, 0x3, 0x2, 0x2, 0x2, 0x37b, 0x37c, 
       0x3, 0x2, 0x2, 0x2, 0x37c, 0x37d, 0x3, 0x2, 0x2, 0x2, 0x37d, 0x37f, 
       0x7, 0x38, 0x2, 0x2, 0x37e, 0x375, 0x3, 0x2, 0x2, 0x2, 0x37e, 0x37f, 
       0x3, 0x2, 0x2, 0x2, 0x37f, 0x381, 0x3, 0x2, 0x2, 0x2, 0x380, 0x382, 
       0x7, 0x72, 0x2, 0x2, 0x381, 0x380, 0x3, 0x2, 0x2, 0x2, 0x381, 0x382, 
       0x3, 0x2, 0x2, 0x2, 0x382, 0x51, 0x3, 0x2, 0x2, 0x2, 0x383, 0x384, 
       0x7, 0xd, 0x2, 0x2, 0x384, 0x386, 0x7, 0x37, 0x2, 0x2, 0x385, 0x387, 
       0x7, 0x67, 0x2, 0x2, 0x386, 0x385, 0x3, 0x2, 0x2, 0x2, 0x386, 0x387, 
       0x3, 0x2, 0x2, 0x2, 0x387, 0x388, 0x3, 0x2, 0x2, 0x2, 0x388, 0x389, 
       0x7, 0x38, 0x2, 0x2, 0x389, 0x38a, 0x7, 0x67, 0x2, 0x2, 0x38a, 0x38b, 
       0x7, 0x37, 0x2, 0x2, 0x38b, 0x396, 0x8, 0x2a, 0x1, 0x2, 0x38c, 0x38d, 
       0x7, 0x67, 0x2, 0x2, 0x38d, 0x393, 0x8, 0x2a, 0x1, 0x2, 0x38e, 0x38f, 
       0x7, 0x5e, 0x2, 0x2, 0x38f, 0x390, 0x7, 0x67, 0x2, 0x2, 0x390, 0x392, 
       0x8, 0x2a, 0x1, 0x2, 0x391, 0x38e, 0x3, 0x2, 0x2, 0x2, 0x392, 0x395, 
       0x3, 0x2, 0x2, 0x2, 0x393, 0x391, 0x3, 0x2, 0x2, 0x2, 0x393, 0x394, 
       0x3, 0x2, 0x2, 0x2, 0x394, 0x397, 0x3, 0x2, 0x2, 0x2, 0x395, 0x393, 
       0x3, 0x2, 0x2, 0x2, 0x396, 0x38c, 0x3, 0x2, 0x2, 0x2, 0x396, 0x397, 
       0x3, 0x2, 0x2, 0x2, 0x397, 0x398, 0x3, 0x2, 0x2, 0x2, 0x398, 0x399, 
       0x7, 0x38, 0x2, 0x2, 0x399, 0x39d, 0x8, 0x2a, 0x1, 0x2, 0x39a, 0x39c, 
       0x7, 0x72, 0x2, 0x2, 0x39b, 0x39a, 0x3, 0x2, 0x2, 0x2, 0x39c, 0x39f, 
       0x3, 0x2, 0x2, 0x2, 0x39d, 0x39b, 0x3, 0x2, 0x2, 0x2, 0x39d, 0x39e, 
       0x3, 0x2, 0x2, 0x2, 0x39e, 0x3a0, 0x3, 0x2, 0x2, 0x2, 0x39f, 0x39d, 
       0x3, 0x2, 0x2, 0x2, 0x3a0, 0x3a4, 0x7, 0x3b, 0x2, 0x2, 0x3a1, 0x3a3, 
       0x7, 0x72, 0x2, 0x2, 0x3a2, 0x3a1, 0x3, 0x2, 0x2, 0x2, 0x3a3, 0x3a6, 
       0x3, 0x2, 0x2, 0x2, 0x3a4, 0x3a2, 0x3, 0x2, 0x2, 0x2, 0x3a4, 0x3a5, 
       0x3, 0x2, 0x2, 0x2, 0x3a5, 0x3a7, 0x3, 0x2, 0x2, 0x2, 0x3a6, 0x3a4, 
       0x3, 0x2, 0x2, 0x2, 0x3a7, 0x3ab, 0x5, 0x54, 0x2b, 0x2, 0x3a8, 0x3aa, 
       0x7, 0x72, 0x2, 0x2, 0x3a9, 0x3a8, 0x3, 0x2, 0x2, 0x2, 0x3aa, 0x3ad, 
       0x3, 0x2, 0x2, 0x2, 0x3ab, 0x3a9, 0x3, 0x2, 0x2, 0x2, 0x3ab, 0x3ac, 
       0x3, 0x2, 0x2, 0x2, 0x3ac, 0x53, 0x3, 0x2, 0x2, 0x2, 0x3ad, 0x3ab, 
       0x3, 0x2, 0x2, 0x2, 0x3ae, 0x3b5, 0x5, 0x56, 0x2c, 0x2, 0x3af, 0x3b0, 
       0x7, 0x3c, 0x2, 0x2, 0x3b0, 0x3b6, 0x7, 0x63, 0x2, 0x2, 0x3b1, 0x3b3, 
       0x7, 0x3c, 0x2, 0x2, 0x3b2, 0x3b1, 0x3, 0x2, 0x2, 0x2, 0x3b2, 0x3b3, 
       0x3, 0x2, 0x2, 0x2, 0x3b3, 0x3b4, 0x3, 0x2, 0x2, 0x2, 0x3b4, 0x3b6, 
       0x5, 0x54, 0x2b, 0x2, 0x3b5, 0x3af, 0x3, 0x2, 0x2, 0x2, 0x3b5, 0x3b2, 
       0x3, 0x2, 0x2, 0x2, 0x3b6, 0x55, 0x3, 0x2, 0x2, 0x2, 0x3b7, 0x3bb, 
       0x7, 0x42, 0x2, 0x2, 0x3b8, 0x3bc, 0x5, 0x8c, 0x47, 0x2, 0x3b9, 0x3bc, 
       0x5, 0x8e, 0x48, 0x2, 0x3ba, 0x3bc, 0x8, 0x2c, 0x1, 0x2, 0x3bb, 0x3b8, 
       0x3, 0x2, 0x2, 0x2, 0x3bb, 0x3b9, 0x3, 0x2, 0x2, 0x2, 0x3bb, 0x3ba, 
       0x3, 0x2, 0x2, 0x2, 0x3bc, 0x3bf, 0x3, 0x2, 0x2, 0x2, 0x3bd, 0x3bf, 
       0x5, 0xbe, 0x60, 0x2, 0x3be, 0x3b7, 0x3, 0x2, 0x2, 0x2, 0x3be, 0x3bd, 
       0x3, 0x2, 0x2, 0x2, 0x3bf, 0x57, 0x3, 0x2, 0x2, 0x2, 0x3c0, 0x3c1, 
       0x7, 0xe, 0x2, 0x2, 0x3c1, 0x3c2, 0x7, 0x37, 0x2, 0x2, 0x3c2, 0x3c3, 
       0x8, 0x2d, 0x1, 0x2, 0x3c3, 0x3c4, 0x5, 0x66, 0x34, 0x2, 0x3c4, 0x3cb, 
       0x8, 0x2d, 0x1, 0x2, 0x3c5, 0x3c6, 0x7, 0x5e, 0x2, 0x2, 0x3c6, 0x3c7, 
       0x5, 0x66, 0x34, 0x2, 0x3c7, 0x3c8, 0x8, 0x2d, 0x1, 0x2, 0x3c8, 0x3ca, 
       0x3, 0x2, 0x2, 0x2, 0x3c9, 0x3c5, 0x3, 0x2, 0x2, 0x2, 0x3ca, 0x3cd, 
       0x3, 0x2, 0x2, 0x2, 0x3cb, 0x3c9, 0x3, 0x2, 0x2, 0x2, 0x3cb, 0x3cc, 
       0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3ce, 0x3, 0x2, 0x2, 0x2, 0x3cd, 0x3cb, 
       0x3, 0x2, 0x2, 0x2, 0x3ce, 0x3d0, 0x7, 0x38, 0x2, 0x2, 0x3cf, 0x3d1, 
       0x5, 0x6c, 0x37, 0x2, 0x3d0, 0x3cf, 0x3, 0x2, 0x2, 0x2, 0x3d0, 0x3d1, 
       0x3, 0x2, 0x2, 0x2, 0x3d1, 0x3d3, 0x3, 0x2, 0x2, 0x2, 0x3d2, 0x3d4, 
       0x7, 0x72, 0x2, 0x2, 0x3d3, 0x3d2, 0x3, 0x2, 0x2, 0x2, 0x3d4, 0x3d5, 
       0x3, 0x2, 0x2, 0x2, 0x3d5, 0x3d3, 0x3, 0x2, 0x2, 0x2, 0x3d5, 0x3d6, 
       0x3, 0x2, 0x2, 0x2, 0x3d6, 0x3d7, 0x3, 0x2, 0x2, 0x2, 0x3d7, 0x3d8, 
       0x5, 0x7e, 0x40, 0x2, 0x3d8, 0x59, 0x3, 0x2, 0x2, 0x2, 0x3d9, 0x3da, 
       0x7, 0x14, 0x2, 0x2, 0x3da, 0x3db, 0x7, 0x37, 0x2, 0x2, 0x3db, 0x3de, 
       0x7, 0x5, 0x2, 0x2, 0x3dc, 0x3dd, 0x7, 0x5e, 0x2, 0x2, 0x3dd, 0x3df, 
       0x7, 0x8, 0x2, 0x2, 0x3de, 0x3dc, 0x3, 0x2, 0x2, 0x2, 0x3de, 0x3df, 
       0x3, 0x2, 0x2, 0x2, 0x3df, 0x3e0, 0x3, 0x2, 0x2, 0x2, 0x3e0, 0x3e1, 
       0x7, 0x38, 0x2, 0x2, 0x3e1, 0x3e2, 0x7, 0x72, 0x2, 0x2, 0x3e2, 0x5b, 
       0x3, 0x2, 0x2, 0x2, 0x3e3, 0x3e4, 0x7, 0x15, 0x2, 0x2, 0x3e4, 0x3e5, 
       0x5, 0x64, 0x33, 0x2, 0x3e5, 0x3e6, 0x7, 0x72, 0x2, 0x2, 0x3e6, 0x5d, 
       0x3, 0x2, 0x2, 0x2, 0x3e7, 0x3e8, 0x7, 0x16, 0x2, 0x2, 0x3e8, 0x3e9, 
       0x5, 0x64, 0x33, 0x2, 0x3e9, 0x3ea, 0x7, 0x72, 0x2, 0x2, 0x3ea, 0x5f, 
       0x3, 0x2, 0x2, 0x2, 0x3eb, 0x3ec, 0x7, 0x17, 0x2, 0x2, 0x3ec, 0x3ed, 
       0x5, 0x64, 0x33, 0x2, 0x3ed, 0x3ee, 0x7, 0x72, 0x2, 0x2, 0x3ee, 0x61, 
       0x3, 0x2, 0x2, 0x2, 0x3ef, 0x3f0, 0x7, 0x18, 0x2, 0x2, 0x3f0, 0x3f1, 
       0x5, 0x64, 0x33, 0x2, 0x3f1, 0x3f2, 0x7, 0x72, 0x2, 0x2, 0x3f2, 0x63, 
       0x3, 0x2, 0x2, 0x2, 0x3f3, 0x3f4, 0x7, 0x37, 0x2, 0x2, 0x3f4, 0x3f5, 
       0x7, 0x67, 0x2, 0x2, 0x3f5, 0x3fb, 0x8, 0x33, 0x1, 0x2, 0x3f6, 0x3f7, 
       0x7, 0x5e, 0x2, 0x2, 0x3f7, 0x3f8, 0x7, 0x67, 0x2, 0x2, 0x3f8, 0x3fa, 
       0x8, 0x33, 0x1, 0x2, 0x3f9, 0x3f6, 0x3, 0x2, 0x2, 0x2, 0x3fa, 0x3fd, 
       0x3, 0x2, 0x2, 0x2, 0x3fb, 0x3f9, 0x3, 0x2, 0x2, 0x2, 0x3fb, 0x3fc, 
       0x3, 0x2, 0x2, 0x2, 0x3fc, 0x3fe, 0x3, 0x2, 0x2, 0x2, 0x3fd, 0x3fb, 
       0x3, 0x2, 0x2, 0x2, 0x3fe, 0x3ff, 0x7, 0x38, 0x2, 0x2, 0x3ff, 0x65, 
       0x3, 0x2, 0x2, 0x2, 0x400, 0x402, 0x7, 0x4d, 0x2, 0x2, 0x401, 0x400, 
       0x3, 0x2, 0x2, 0x2, 0x401, 0x402, 0x3, 0x2, 0x2, 0x2, 0x402, 0x403, 
       0x3, 0x2, 0x2, 0x2, 0x403, 0x404, 0x5, 0x68, 0x35, 0x2, 0x404, 0x67, 
       0x3, 0x2, 0x2, 0x2, 0x405, 0x406, 0x6, 0x35, 0x3, 0x2, 0x406, 0x409, 
       0x7, 0x67, 0x2, 0x2, 0x407, 0x409, 0x8, 0x35, 0x1, 0x2, 0x408, 0x405, 
       0x3, 0x2, 0x2, 0x2, 0x408, 0x407, 0x3, 0x2, 0x2, 0x2, 0x409, 0x69, 
       0x3, 0x2, 0x2, 0x2, 0x40a, 0x417, 0x7, 0x67, 0x2, 0x2, 0x40b, 0x414, 
       0x7, 0x37, 0x2, 0x2, 0x40c, 0x411, 0x5, 0x6a, 0x36, 0x2, 0x40d, 0x40e, 
       0x7, 0x5e, 0x2, 0x2, 0x40e, 0x410, 0x5, 0x6a, 0x36, 0x2, 0x40f, 0x40d, 
       0x3, 0x2, 0x2, 0x2, 0x410, 0x413, 0x3, 0x2, 0x2, 0x2, 0x411, 0x40f, 
       0x3, 0x2, 0x2, 0x2, 0x411, 0x412, 0x3, 0x2, 0x2, 0x2, 0x412, 0x415, 
       0x3, 0x2, 0x2, 0x2, 0x413, 0x411, 0x3, 0x2, 0x2, 0x2, 0x414, 0x40c, 
       0x3, 0x2, 0x2, 0x2, 0x414, 0x415, 0x3, 0x2, 0x2, 0x2, 0x415, 0x416, 
       0x3, 0x2, 0x2, 0x2, 0x416, 0x418, 0x7, 0x38, 0x2, 0x2, 0x417, 0x40b, 
       0x3, 0x2, 0x2, 0x2, 0x417, 0x418, 0x3, 0x2, 0x2, 0x2, 0x418, 0x427, 
       0x3, 0x2, 0x2, 0x2, 0x419, 0x41b, 0xa, 0x7, 0x2, 0x2, 0x41a, 0x419, 
       0x3, 0x2, 0x2, 0x2, 0x41b, 0x41c, 0x3, 0x2, 0x2, 0x2, 0x41c, 0x41a, 
       0x3, 0x2, 0x2, 0x2, 0x41c, 0x41d, 0x3, 0x2, 0x2, 0x2, 0x41d, 0x427, 
       0x3, 0x2, 0x2, 0x2, 0x41e, 0x41f, 0x7, 0x37, 0x2, 0x2, 0x41f, 0x420, 
       0x5, 0x6a, 0x36, 0x2, 0x420, 0x421, 0x7, 0x38, 0x2, 0x2, 0x421, 0x427, 
       0x3, 0x2, 0x2, 0x2, 0x422, 0x423, 0x7, 0x39, 0x2, 0x2, 0x423, 0x424, 
       0x5, 0x6a, 0x36, 0x2, 0x424, 0x425, 0x7, 0x3a, 0x2, 0x2, 0x425, 0x427, 
       0x3, 0x2, 0x2, 0x2, 0x426, 0x40a, 0x3, 0x2, 0x2, 0x2, 0x426, 0x41a, 
       0x3, 0x2, 0x2, 0x2, 0x426, 0x41e, 0x3, 0x2, 0x2, 0x2, 0x426, 0x422, 
       0x3, 0x2, 0x2, 0x2, 0x427, 0x429, 0x3, 0x2, 0x2, 0x2, 0x428, 0x42a, 
       0x5, 0x6a, 0x36, 0x2, 0x429, 0x428, 0x3, 0x2, 0x2, 0x2, 0x429, 0x42a, 
       0x3, 0x2, 0x2, 0x2, 0x42a, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x42b, 0x42f, 
       0x5, 0x6e, 0x38, 0x2, 0x42c, 0x42f, 0x5, 0x70, 0x39, 0x2, 0x42d, 
       0x42f, 0x5, 0x72, 0x3a, 0x2, 0x42e, 0x42b, 0x3, 0x2, 0x2, 0x2, 0x42e, 
       0x42c, 0x3, 0x2, 0x2, 0x2, 0x42e, 0x42d, 0x3, 0x2, 0x2, 0x2, 0x42f, 
       0x431, 0x3, 0x2, 0x2, 0x2, 0x430, 0x432, 0x5, 0x78, 0x3d, 0x2, 0x431, 
       0x430, 0x3, 0x2, 0x2, 0x2, 0x431, 0x432, 0x3, 0x2, 0x2, 0x2, 0x432, 
       0x6d, 0x3, 0x2, 0x2, 0x2, 0x433, 0x434, 0x7, 0x29, 0x2, 0x2, 0x434, 
       0x435, 0x7, 0x37, 0x2, 0x2, 0x435, 0x436, 0x9, 0x8, 0x2, 0x2, 0x436, 
       0x437, 0x7, 0x38, 0x2, 0x2, 0x437, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x438, 
       0x439, 0x7, 0x25, 0x2, 0x2, 0x439, 0x43a, 0x7, 0x37, 0x2, 0x2, 0x43a, 
       0x43b, 0x9, 0x9, 0x2, 0x2, 0x43b, 0x43c, 0x7, 0x5e, 0x2, 0x2, 0x43c, 
       0x43d, 0x7, 0x7, 0x2, 0x2, 0x43d, 0x43e, 0x7, 0x5e, 0x2, 0x2, 0x43e, 
       0x445, 0x7, 0x5, 0x2, 0x2, 0x43f, 0x440, 0x7, 0x5e, 0x2, 0x2, 0x440, 
       0x443, 0x5, 0x74, 0x3b, 0x2, 0x441, 0x442, 0x7, 0x5e, 0x2, 0x2, 0x442, 
       0x444, 0x5, 0x74, 0x3b, 0x2, 0x443, 0x441, 0x3, 0x2, 0x2, 0x2, 0x443, 
       0x444, 0x3, 0x2, 0x2, 0x2, 0x444, 0x446, 0x3, 0x2, 0x2, 0x2, 0x445, 
       0x43f, 0x3, 0x2, 0x2, 0x2, 0x445, 0x446, 0x3, 0x2, 0x2, 0x2, 0x446, 
       0x447, 0x3, 0x2, 0x2, 0x2, 0x447, 0x448, 0x7, 0x38, 0x2, 0x2, 0x448, 
       0x71, 0x3, 0x2, 0x2, 0x2, 0x449, 0x44a, 0x7, 0x28, 0x2, 0x2, 0x44a, 
       0x44b, 0x7, 0x37, 0x2, 0x2, 0x44b, 0x44c, 0x9, 0x9, 0x2, 0x2, 0x44c, 
       0x44d, 0x7, 0x5e, 0x2, 0x2, 0x44d, 0x44e, 0x7, 0x5, 0x2, 0x2, 0x44e, 
       0x44f, 0x7, 0x38, 0x2, 0x2, 0x44f, 0x73, 0x3, 0x2, 0x2, 0x2, 0x450, 
       0x451, 0x7, 0x5, 0x2, 0x2, 0x451, 0x452, 0x7, 0x5e, 0x2, 0x2, 0x452, 
       0x453, 0x5, 0x76, 0x3c, 0x2, 0x453, 0x75, 0x3, 0x2, 0x2, 0x2, 0x454, 
       0x455, 0x6, 0x3c, 0x4, 0x2, 0x455, 0x458, 0x7, 0x67, 0x2, 0x2, 0x456, 
       0x458, 0x8, 0x3c, 0x1, 0x2, 0x457, 0x454, 0x3, 0x2, 0x2, 0x2, 0x457, 
       0x456, 0x3, 0x2, 0x2, 0x2, 0x458, 0x77, 0x3, 0x2, 0x2, 0x2, 0x459, 
       0x45c, 0x5, 0x7a, 0x3e, 0x2, 0x45a, 0x45c, 0x5, 0x7c, 0x3f, 0x2, 
       0x45b, 0x459, 0x3, 0x2, 0x2, 0x2, 0x45b, 0x45a, 0x3, 0x2, 0x2, 0x2, 
       0x45c, 0x79, 0x3, 0x2, 0x2, 0x2, 0x45d, 0x45e, 0x7, 0x22, 0x2, 0x2, 
       0x45e, 0x45f, 0x7, 0x37, 0x2, 0x2, 0x45f, 0x460, 0x7, 0x5, 0x2, 0x2, 
       0x460, 0x461, 0x7, 0x5e, 0x2, 0x2, 0x461, 0x462, 0x7, 0x5, 0x2, 0x2, 
       0x462, 0x463, 0x7, 0x38, 0x2, 0x2, 0x463, 0x7b, 0x3, 0x2, 0x2, 0x2, 
       0x464, 0x465, 0x7, 0x21, 0x2, 0x2, 0x465, 0x466, 0x7, 0x37, 0x2, 
       0x2, 0x466, 0x467, 0x5, 0x6a, 0x36, 0x2, 0x467, 0x468, 0x7, 0x5e, 
       0x2, 0x2, 0x468, 0x469, 0x5, 0x6a, 0x36, 0x2, 0x469, 0x46a, 0x7, 
       0x38, 0x2, 0x2, 0x46a, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x46b, 0x46d, 0x5, 
       0x80, 0x41, 0x2, 0x46c, 0x46b, 0x3, 0x2, 0x2, 0x2, 0x46d, 0x46e, 
       0x3, 0x2, 0x2, 0x2, 0x46e, 0x46c, 0x3, 0x2, 0x2, 0x2, 0x46e, 0x46f, 
       0x3, 0x2, 0x2, 0x2, 0x46f, 0x470, 0x3, 0x2, 0x2, 0x2, 0x470, 0x471, 
       0x7, 0x67, 0x2, 0x2, 0x471, 0x472, 0x7, 0x37, 0x2, 0x2, 0x472, 0x47e, 
       0x8, 0x40, 0x1, 0x2, 0x473, 0x474, 0x5, 0x88, 0x45, 0x2, 0x474, 0x47b, 
       0x8, 0x40, 0x1, 0x2, 0x475, 0x476, 0x7, 0x5e, 0x2, 0x2, 0x476, 0x477, 
       0x5, 0x88, 0x45, 0x2, 0x477, 0x478, 0x8, 0x40, 0x1, 0x2, 0x478, 0x47a, 
       0x3, 0x2, 0x2, 0x2, 0x479, 0x475, 0x3, 0x2, 0x2, 0x2, 0x47a, 0x47d, 
       0x3, 0x2, 0x2, 0x2, 0x47b, 0x479, 0x3, 0x2, 0x2, 0x2, 0x47b, 0x47c, 
       0x3, 0x2, 0x2, 0x2, 0x47c, 0x47f, 0x3, 0x2, 0x2, 0x2, 0x47d, 0x47b, 
       0x3, 0x2, 0x2, 0x2, 0x47e, 0x473, 0x3, 0x2, 0x2, 0x2, 0x47e, 0x47f, 
       0x3, 0x2, 0x2, 0x2, 0x47f, 0x480, 0x3, 0x2, 0x2, 0x2, 0x480, 0x481, 
       0x7, 0x38, 0x2, 0x2, 0x481, 0x485, 0x8, 0x40, 0x1, 0x2, 0x482, 0x484, 
       0x7, 0x72, 0x2, 0x2, 0x483, 0x482, 0x3, 0x2, 0x2, 0x2, 0x484, 0x487, 
       0x3, 0x2, 0x2, 0x2, 0x485, 0x483, 0x3, 0x2, 0x2, 0x2, 0x485, 0x486, 
       0x3, 0x2, 0x2, 0x2, 0x486, 0x488, 0x3, 0x2, 0x2, 0x2, 0x487, 0x485, 
       0x3, 0x2, 0x2, 0x2, 0x488, 0x48c, 0x7, 0x3b, 0x2, 0x2, 0x489, 0x48b, 
       0xa, 0xa, 0x2, 0x2, 0x48a, 0x489, 0x3, 0x2, 0x2, 0x2, 0x48b, 0x48e, 
       0x3, 0x2, 0x2, 0x2, 0x48c, 0x48a, 0x3, 0x2, 0x2, 0x2, 0x48c, 0x48d, 
       0x3, 0x2, 0x2, 0x2, 0x48d, 0x490, 0x3, 0x2, 0x2, 0x2, 0x48e, 0x48c, 
       0x3, 0x2, 0x2, 0x2, 0x48f, 0x491, 0x7, 0x72, 0x2, 0x2, 0x490, 0x48f, 
       0x3, 0x2, 0x2, 0x2, 0x491, 0x492, 0x3, 0x2, 0x2, 0x2, 0x492, 0x490, 
       0x3, 0x2, 0x2, 0x2, 0x492, 0x493, 0x3, 0x2, 0x2, 0x2, 0x493, 0x7f, 
       0x3, 0x2, 0x2, 0x2, 0x494, 0x49d, 0x5, 0x82, 0x42, 0x2, 0x495, 0x49e, 
       0x7, 0x51, 0x2, 0x2, 0x496, 0x49e, 0x7, 0x5c, 0x2, 0x2, 0x497, 0x499, 
       0x7, 0x4d, 0x2, 0x2, 0x498, 0x497, 0x3, 0x2, 0x2, 0x2, 0x499, 0x49c, 
       0x3, 0x2, 0x2, 0x2, 0x49a, 0x498, 0x3, 0x2, 0x2, 0x2, 0x49a, 0x49b, 
       0x3, 0x2, 0x2, 0x2, 0x49b, 0x49e, 0x3, 0x2, 0x2, 0x2, 0x49c, 0x49a, 
       0x3, 0x2, 0x2, 0x2, 0x49d, 0x495, 0x3, 0x2, 0x2, 0x2, 0x49d, 0x496, 
       0x3, 0x2, 0x2, 0x2, 0x49d, 0x49a, 0x3, 0x2, 0x2, 0x2, 0x49e, 0x81, 
       0x3, 0x2, 0x2, 0x2, 0x49f, 0x4ab, 0x7, 0x67, 0x2, 0x2, 0x4a0, 0x4a2, 
       0x7, 0x56, 0x2, 0x2, 0x4a1, 0x4a3, 0x5, 0x84, 0x43, 0x2, 0x4a2, 0x4a1, 
       0x3, 0x2, 0x2, 0x2, 0x4a2, 0x4a3, 0x3, 0x2, 0x2, 0x2, 0x4a3, 0x4a4, 
       0x3, 0x2, 0x2, 0x2, 0x4a4, 0x4ac, 0x7, 0x57, 0x2, 0x2, 0x4a5, 0x4a7, 
       0x7, 0x67, 0x2, 0x2, 0x4a6, 0x4a5, 0x3, 0x2, 0x2, 0x2, 0x4a7, 0x4aa, 
       0x3, 0x2, 0x2, 0x2, 0x4a8, 0x4a6, 0x3, 0x2, 0x2, 0x2, 0x4a8, 0x4a9, 
       0x3, 0x2, 0x2, 0x2, 0x4a9, 0x4ac, 0x3, 0x2, 0x2, 0x2, 0x4aa, 0x4a8, 
       0x3, 0x2, 0x2, 0x2, 0x4ab, 0x4a0, 0x3, 0x2, 0x2, 0x2, 0x4ab, 0x4a8, 
       0x3, 0x2, 0x2, 0x2, 0x4ac, 0x83, 0x3, 0x2, 0x2, 0x2, 0x4ad, 0x4b2, 
       0x5, 0x86, 0x44, 0x2, 0x4ae, 0x4af, 0x7, 0x5e, 0x2, 0x2, 0x4af, 0x4b1, 
       0x5, 0x86, 0x44, 0x2, 0x4b0, 0x4ae, 0x3, 0x2, 0x2, 0x2, 0x4b1, 0x4b4, 
       0x3, 0x2, 0x2, 0x2, 0x4b2, 0x4b0, 0x3, 0x2, 0x2, 0x2, 0x4b2, 0x4b3, 
       0x3, 0x2, 0x2, 0x2, 0x4b3, 0x85, 0x3, 0x2, 0x2, 0x2, 0x4b4, 0x4b2, 
       0x3, 0x2, 0x2, 0x2, 0x4b5, 0x4b8, 0x5, 0x82, 0x42, 0x2, 0x4b6, 0x4b8, 
       0x5, 0xce, 0x68, 0x2, 0x4b7, 0x4b5, 0x3, 0x2, 0x2, 0x2, 0x4b7, 0x4b6, 
       0x3, 0x2, 0x2, 0x2, 0x4b8, 0x87, 0x3, 0x2, 0x2, 0x2, 0x4b9, 0x4ba, 
       0x5, 0x80, 0x41, 0x2, 0x4ba, 0x4be, 0x7, 0x67, 0x2, 0x2, 0x4bb, 0x4bd, 
       0x5, 0x8a, 0x46, 0x2, 0x4bc, 0x4bb, 0x3, 0x2, 0x2, 0x2, 0x4bd, 0x4c0, 
       0x3, 0x2, 0x2, 0x2, 0x4be, 0x4bc, 0x3, 0x2, 0x2, 0x2, 0x4be, 0x4bf, 
       0x3, 0x2, 0x2, 0x2, 0x4bf, 0x89, 0x3, 0x2, 0x2, 0x2, 0x4c0, 0x4be, 
       0x3, 0x2, 0x2, 0x2, 0x4c1, 0x4c2, 0x7, 0x39, 0x2, 0x2, 0x4c2, 0x4c3, 
       0x9, 0xb, 0x2, 0x2, 0x4c3, 0x4c4, 0x7, 0x3a, 0x2, 0x2, 0x4c4, 0x8b, 
       0x3, 0x2, 0x2, 0x2, 0x4c5, 0x4c6, 0x7, 0x27, 0x2, 0x2, 0x4c6, 0x4c7, 
       0x7, 0x43, 0x2, 0x2, 0x4c7, 0x4c8, 0x5, 0x92, 0x4a, 0x2, 0x4c8, 0x4c9, 
       0x7, 0x64, 0x2, 0x2, 0x4c9, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x4ca, 0x4cc, 
       0x7, 0x67, 0x2, 0x2, 0x4cb, 0x4cd, 0x5, 0x90, 0x49, 0x2, 0x4cc, 0x4cb, 
       0x3, 0x2, 0x2, 0x2, 0x4cc, 0x4cd, 0x3, 0x2, 0x2, 0x2, 0x4cd, 0x4d0, 
       0x3, 0x2, 0x2, 0x2, 0x4ce, 0x4cf, 0x7, 0x43, 0x2, 0x2, 0x4cf, 0x4d1, 
       0x5, 0x92, 0x4a, 0x2, 0x4d0, 0x4ce, 0x3, 0x2, 0x2, 0x2, 0x4d0, 0x4d1, 
       0x3, 0x2, 0x2, 0x2, 0x4d1, 0x4d2, 0x3, 0x2, 0x2, 0x2, 0x4d2, 0x4d3, 
       0x7, 0x64, 0x2, 0x2, 0x4d3, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x4d4, 0x4d5, 
       0x7, 0x37, 0x2, 0x2, 0x4d5, 0x4da, 0x5, 0x94, 0x4b, 0x2, 0x4d6, 0x4d7, 
       0x7, 0x5e, 0x2, 0x2, 0x4d7, 0x4d9, 0x5, 0x94, 0x4b, 0x2, 0x4d8, 0x4d6, 
       0x3, 0x2, 0x2, 0x2, 0x4d9, 0x4dc, 0x3, 0x2, 0x2, 0x2, 0x4da, 0x4d8, 
       0x3, 0x2, 0x2, 0x2, 0x4da, 0x4db, 0x3, 0x2, 0x2, 0x2, 0x4db, 0x4dd, 
       0x3, 0x2, 0x2, 0x2, 0x4dc, 0x4da, 0x3, 0x2, 0x2, 0x2, 0x4dd, 0x4de, 
       0x7, 0x38, 0x2, 0x2, 0x4de, 0x91, 0x3, 0x2, 0x2, 0x2, 0x4df, 0x4e1, 
       0x7, 0x72, 0x2, 0x2, 0x4e0, 0x4df, 0x3, 0x2, 0x2, 0x2, 0x4e1, 0x4e4, 
       0x3, 0x2, 0x2, 0x2, 0x4e2, 0x4e0, 0x3, 0x2, 0x2, 0x2, 0x4e2, 0x4e3, 
       0x3, 0x2, 0x2, 0x2, 0x4e3, 0x4e6, 0x3, 0x2, 0x2, 0x2, 0x4e4, 0x4e2, 
       0x3, 0x2, 0x2, 0x2, 0x4e5, 0x4e7, 0x7, 0x45, 0x2, 0x2, 0x4e6, 0x4e5, 
       0x3, 0x2, 0x2, 0x2, 0x4e6, 0x4e7, 0x3, 0x2, 0x2, 0x2, 0x4e7, 0x4e8, 
       0x3, 0x2, 0x2, 0x2, 0x4e8, 0x4ea, 0x5, 0x9a, 0x4e, 0x2, 0x4e9, 0x4eb, 
       0x5, 0x9c, 0x4f, 0x2, 0x4ea, 0x4e9, 0x3, 0x2, 0x2, 0x2, 0x4ea, 0x4eb, 
       0x3, 0x2, 0x2, 0x2, 0x4eb, 0x4ee, 0x3, 0x2, 0x2, 0x2, 0x4ec, 0x4ed, 
       0x9, 0xc, 0x2, 0x2, 0x4ed, 0x4ef, 0x5, 0x92, 0x4a, 0x2, 0x4ee, 0x4ec, 
       0x3, 0x2, 0x2, 0x2, 0x4ee, 0x4ef, 0x3, 0x2, 0x2, 0x2, 0x4ef, 0x93, 
       0x3, 0x2, 0x2, 0x2, 0x4f0, 0x4f6, 0x5, 0xce, 0x68, 0x2, 0x4f1, 0x4f6, 
       0x7, 0x9, 0x2, 0x2, 0x4f2, 0x4f6, 0x5, 0x96, 0x4c, 0x2, 0x4f3, 0x4f6, 
       0x5, 0x9a, 0x4e, 0x2, 0x4f4, 0x4f6, 0x7, 0x4a, 0x2, 0x2, 0x4f5, 0x4f0, 
       0x3, 0x2, 0x2, 0x2, 0x4f5, 0x4f1, 0x3, 0x2, 0x2, 0x2, 0x4f5, 0x4f2, 
       0x3, 0x2, 0x2, 0x2, 0x4f5, 0x4f3, 0x3, 0x2, 0x2, 0x2, 0x4f5, 0x4f4, 
       0x3, 0x2, 0x2, 0x2, 0x4f6, 0x95, 0x3, 0x2, 0x2, 0x2, 0x4f7, 0x4fd, 
       0x7, 0x39, 0x2, 0x2, 0x4f8, 0x4fb, 0x5, 0x98, 0x4d, 0x2, 0x4f9, 0x4fa, 
       0x7, 0x52, 0x2, 0x2, 0x4fa, 0x4fc, 0x5, 0x94, 0x4b, 0x2, 0x4fb, 0x4f9, 
       0x3, 0x2, 0x2, 0x2, 0x4fb, 0x4fc, 0x3, 0x2, 0x2, 0x2, 0x4fc, 0x4fe, 
       0x3, 0x2, 0x2, 0x2, 0x4fd, 0x4f8, 0x3, 0x2, 0x2, 0x2, 0x4fd, 0x4fe, 
       0x3, 0x2, 0x2, 0x2, 0x4fe, 0x4ff, 0x3, 0x2, 0x2, 0x2, 0x4ff, 0x500, 
       0x7, 0x3a, 0x2, 0x2, 0x500, 0x97, 0x3, 0x2, 0x2, 0x2, 0x501, 0x504, 
       0x5, 0x94, 0x4b, 0x2, 0x502, 0x503, 0x7, 0x5e, 0x2, 0x2, 0x503, 0x505, 
       0x5, 0x98, 0x4d, 0x2, 0x504, 0x502, 0x3, 0x2, 0x2, 0x2, 0x504, 0x505, 
       0x3, 0x2, 0x2, 0x2, 0x505, 0x99, 0x3, 0x2, 0x2, 0x2, 0x506, 0x50a, 
       0x7, 0x37, 0x2, 0x2, 0x507, 0x509, 0x7, 0x72, 0x2, 0x2, 0x508, 0x507, 
       0x3, 0x2, 0x2, 0x2, 0x509, 0x50c, 0x3, 0x2, 0x2, 0x2, 0x50a, 0x508, 
       0x3, 0x2, 0x2, 0x2, 0x50a, 0x50b, 0x3, 0x2, 0x2, 0x2, 0x50b, 0x50d, 
       0x3, 0x2, 0x2, 0x2, 0x50c, 0x50a, 0x3, 0x2, 0x2, 0x2, 0x50d, 0x511, 
       0x5, 0x92, 0x4a, 0x2, 0x50e, 0x510, 0x7, 0x72, 0x2, 0x2, 0x50f, 0x50e, 
       0x3, 0x2, 0x2, 0x2, 0x510, 0x513, 0x3, 0x2, 0x2, 0x2, 0x511, 0x50f, 
       0x3, 0x2, 0x2, 0x2, 0x511, 0x512, 0x3, 0x2, 0x2, 0x2, 0x512, 0x514, 
       0x3, 0x2, 0x2, 0x2, 0x513, 0x511, 0x3, 0x2, 0x2, 0x2, 0x514, 0x518, 
       0x7, 0x38, 0x2, 0x2, 0x515, 0x517, 0x7, 0x72, 0x2, 0x2, 0x516, 0x515, 
       0x3, 0x2, 0x2, 0x2, 0x517, 0x51a, 0x3, 0x2, 0x2, 0x2, 0x518, 0x516, 
       0x3, 0x2, 0x2, 0x2, 0x518, 0x519, 0x3, 0x2, 0x2, 0x2, 0x519, 0x51f, 
       0x3, 0x2, 0x2, 0x2, 0x51a, 0x518, 0x3, 0x2, 0x2, 0x2, 0x51b, 0x51f, 
       0x7, 0x54, 0x2, 0x2, 0x51c, 0x51f, 0x5, 0xb8, 0x5d, 0x2, 0x51d, 0x51f, 
       0x5, 0x9e, 0x50, 0x2, 0x51e, 0x506, 0x3, 0x2, 0x2, 0x2, 0x51e, 0x51b, 
       0x3, 0x2, 0x2, 0x2, 0x51e, 0x51c, 0x3, 0x2, 0x2, 0x2, 0x51e, 0x51d, 
       0x3, 0x2, 0x2, 0x2, 0x51f, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x520, 0x524, 
       0x7, 0x5f, 0x2, 0x2, 0x521, 0x523, 0x7, 0x72, 0x2, 0x2, 0x522, 0x521, 
       0x3, 0x2, 0x2, 0x2, 0x523, 0x526, 0x3, 0x2, 0x2, 0x2, 0x524, 0x522, 
       0x3, 0x2, 0x2, 0x2, 0x524, 0x525, 0x3, 0x2, 0x2, 0x2, 0x525, 0x528, 
       0x3, 0x2, 0x2, 0x2, 0x526, 0x524, 0x3, 0x2, 0x2, 0x2, 0x527, 0x529, 
       0x7, 0x45, 0x2, 0x2, 0x528, 0x527, 0x3, 0x2, 0x2, 0x2, 0x528, 0x529, 
       0x3, 0x2, 0x2, 0x2, 0x529, 0x52a, 0x3, 0x2, 0x2, 0x2, 0x52a, 0x52b, 
       0x5, 0x9a, 0x4e, 0x2, 0x52b, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x52c, 0x52f, 
       0x5, 0xa0, 0x51, 0x2, 0x52d, 0x52e, 0x7, 0x44, 0x2, 0x2, 0x52e, 0x530, 
       0x5, 0xa0, 0x51, 0x2, 0x52f, 0x52d, 0x3, 0x2, 0x2, 0x2, 0x52f, 0x530, 
       0x3, 0x2, 0x2, 0x2, 0x530, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x531, 0x535, 
       0x5, 0xa4, 0x53, 0x2, 0x532, 0x533, 0x5, 0xa2, 0x52, 0x2, 0x533, 
       0x534, 0x5, 0xa0, 0x51, 0x2, 0x534, 0x536, 0x3, 0x2, 0x2, 0x2, 0x535, 
       0x532, 0x3, 0x2, 0x2, 0x2, 0x535, 0x536, 0x3, 0x2, 0x2, 0x2, 0x536, 
       0xa1, 0x3, 0x2, 0x2, 0x2, 0x537, 0x538, 0x9, 0xd, 0x2, 0x2, 0x538, 
       0xa3, 0x3, 0x2, 0x2, 0x2, 0x539, 0x53d, 0x5, 0xa8, 0x55, 0x2, 0x53a, 
       0x53b, 0x5, 0xa6, 0x54, 0x2, 0x53b, 0x53c, 0x5, 0xa4, 0x53, 0x2, 
       0x53c, 0x53e, 0x3, 0x2, 0x2, 0x2, 0x53d, 0x53a, 0x3, 0x2, 0x2, 0x2, 
       0x53d, 0x53e, 0x3, 0x2, 0x2, 0x2, 0x53e, 0xa5, 0x3, 0x2, 0x2, 0x2, 
       0x53f, 0x540, 0x7, 0x4d, 0x2, 0x2, 0x540, 0x543, 0x7, 0x4d, 0x2, 
       0x2, 0x541, 0x543, 0x7, 0x50, 0x2, 0x2, 0x542, 0x53f, 0x3, 0x2, 0x2, 
       0x2, 0x542, 0x541, 0x3, 0x2, 0x2, 0x2, 0x543, 0xa7, 0x3, 0x2, 0x2, 
       0x2, 0x544, 0x548, 0x5, 0xac, 0x57, 0x2, 0x545, 0x546, 0x5, 0xaa, 
       0x56, 0x2, 0x546, 0x547, 0x5, 0xa8, 0x55, 0x2, 0x547, 0x549, 0x3, 
       0x2, 0x2, 0x2, 0x548, 0x545, 0x3, 0x2, 0x2, 0x2, 0x548, 0x549, 0x3, 
       0x2, 0x2, 0x2, 0x549, 0xa9, 0x3, 0x2, 0x2, 0x2, 0x54a, 0x553, 0x7, 
       0x4d, 0x2, 0x2, 0x54b, 0x553, 0x7, 0x31, 0x2, 0x2, 0x54c, 0x553, 
       0x7, 0x23, 0x2, 0x2, 0x54d, 0x553, 0x7, 0x2a, 0x2, 0x2, 0x54e, 0x550, 
       0x7, 0x4e, 0x2, 0x2, 0x54f, 0x551, 0x7, 0x4e, 0x2, 0x2, 0x550, 0x54f, 
       0x3, 0x2, 0x2, 0x2, 0x550, 0x551, 0x3, 0x2, 0x2, 0x2, 0x551, 0x553, 
       0x3, 0x2, 0x2, 0x2, 0x552, 0x54a, 0x3, 0x2, 0x2, 0x2, 0x552, 0x54b, 
       0x3, 0x2, 0x2, 0x2, 0x552, 0x54c, 0x3, 0x2, 0x2, 0x2, 0x552, 0x54d, 
       0x3, 0x2, 0x2, 0x2, 0x552, 0x54e, 0x3, 0x2, 0x2, 0x2, 0x553, 0xab, 
       0x3, 0x2, 0x2, 0x2, 0x554, 0x55a, 0x5, 0xb0, 0x59, 0x2, 0x555, 0x556, 
       0x5, 0xae, 0x58, 0x2, 0x556, 0x557, 0x5, 0xac, 0x57, 0x2, 0x557, 
       0x559, 0x3, 0x2, 0x2, 0x2, 0x558, 0x555, 0x3, 0x2, 0x2, 0x2, 0x559, 
       0x55c, 0x3, 0x2, 0x2, 0x2, 0x55a, 0x558, 0x3, 0x2, 0x2, 0x2, 0x55a, 
       0x55b, 0x3, 0x2, 0x2, 0x2, 0x55b, 0xad, 0x3, 0x2, 0x2, 0x2, 0x55c, 
       0x55a, 0x3, 0x2, 0x2, 0x2, 0x55d, 0x55e, 0x9, 0x4, 0x2, 0x2, 0x55e, 
       0xaf, 0x3, 0x2, 0x2, 0x2, 0x55f, 0x561, 0x5, 0xae, 0x58, 0x2, 0x560, 
       0x55f, 0x3, 0x2, 0x2, 0x2, 0x560, 0x561, 0x3, 0x2, 0x2, 0x2, 0x561, 
       0x562, 0x3, 0x2, 0x2, 0x2, 0x562, 0x563, 0x5, 0xb2, 0x5a, 0x2, 0x563, 
       0xb1, 0x3, 0x2, 0x2, 0x2, 0x564, 0x565, 0x7, 0x37, 0x2, 0x2, 0x565, 
       0x566, 0x5, 0xa0, 0x51, 0x2, 0x566, 0x567, 0x7, 0x38, 0x2, 0x2, 0x567, 
       0x56d, 0x3, 0x2, 0x2, 0x2, 0x568, 0x56d, 0x5, 0xb4, 0x5b, 0x2, 0x569, 
       0x56d, 0x5, 0xb6, 0x5c, 0x2, 0x56a, 0x56d, 0x7, 0x9, 0x2, 0x2, 0x56b, 
       0x56d, 0x5, 0xce, 0x68, 0x2, 0x56c, 0x564, 0x3, 0x2, 0x2, 0x2, 0x56c, 
       0x568, 0x3, 0x2, 0x2, 0x2, 0x56c, 0x569, 0x3, 0x2, 0x2, 0x2, 0x56c, 
       0x56a, 0x3, 0x2, 0x2, 0x2, 0x56c, 0x56b, 0x3, 0x2, 0x2, 0x2, 0x56d, 
       0xb3, 0x3, 0x2, 0x2, 0x2, 0x56e, 0x57b, 0x7, 0x39, 0x2, 0x2, 0x56f, 
       0x574, 0x5, 0xa0, 0x51, 0x2, 0x570, 0x571, 0x7, 0x5e, 0x2, 0x2, 0x571, 
       0x573, 0x5, 0xa0, 0x51, 0x2, 0x572, 0x570, 0x3, 0x2, 0x2, 0x2, 0x573, 
       0x576, 0x3, 0x2, 0x2, 0x2, 0x574, 0x572, 0x3, 0x2, 0x2, 0x2, 0x574, 
       0x575, 0x3, 0x2, 0x2, 0x2, 0x575, 0x579, 0x3, 0x2, 0x2, 0x2, 0x576, 
       0x574, 0x3, 0x2, 0x2, 0x2, 0x577, 0x578, 0x7, 0x52, 0x2, 0x2, 0x578, 
       0x57a, 0x5, 0xa0, 0x51, 0x2, 0x579, 0x577, 0x3, 0x2, 0x2, 0x2, 0x579, 
       0x57a, 0x3, 0x2, 0x2, 0x2, 0x57a, 0x57c, 0x3, 0x2, 0x2, 0x2, 0x57b, 
       0x56f, 0x3, 0x2, 0x2, 0x2, 0x57b, 0x57c, 0x3, 0x2, 0x2, 0x2, 0x57c, 
       0x57d, 0x3, 0x2, 0x2, 0x2, 0x57d, 0x57e, 0x7, 0x3a, 0x2, 0x2, 0x57e, 
       0xb5, 0x3, 0x2, 0x2, 0x2, 0x57f, 0x58c, 0x7, 0x67, 0x2, 0x2, 0x580, 
       0x589, 0x7, 0x37, 0x2, 0x2, 0x581, 0x586, 0x5, 0xa0, 0x51, 0x2, 0x582, 
       0x583, 0x7, 0x5e, 0x2, 0x2, 0x583, 0x585, 0x5, 0xa0, 0x51, 0x2, 0x584, 
       0x582, 0x3, 0x2, 0x2, 0x2, 0x585, 0x588, 0x3, 0x2, 0x2, 0x2, 0x586, 
       0x584, 0x3, 0x2, 0x2, 0x2, 0x586, 0x587, 0x3, 0x2, 0x2, 0x2, 0x587, 
       0x58a, 0x3, 0x2, 0x2, 0x2, 0x588, 0x586, 0x3, 0x2, 0x2, 0x2, 0x589, 
       0x581, 0x3, 0x2, 0x2, 0x2, 0x589, 0x58a, 0x3, 0x2, 0x2, 0x2, 0x58a, 
       0x58b, 0x3, 0x2, 0x2, 0x2, 0x58b, 0x58d, 0x7, 0x38, 0x2, 0x2, 0x58c, 
       0x580, 0x3, 0x2, 0x2, 0x2, 0x58c, 0x58d, 0x3, 0x2, 0x2, 0x2, 0x58d, 
       0xb7, 0x3, 0x2, 0x2, 0x2, 0x58e, 0x58f, 0x5, 0xbc, 0x5f, 0x2, 0x58f, 
       0x590, 0x5, 0xba, 0x5e, 0x2, 0x590, 0x596, 0x3, 0x2, 0x2, 0x2, 0x591, 
       0x593, 0x7, 0x67, 0x2, 0x2, 0x592, 0x594, 0x5, 0xba, 0x5e, 0x2, 0x593, 
       0x592, 0x3, 0x2, 0x2, 0x2, 0x593, 0x594, 0x3, 0x2, 0x2, 0x2, 0x594, 
       0x596, 0x3, 0x2, 0x2, 0x2, 0x595, 0x58e, 0x3, 0x2, 0x2, 0x2, 0x595, 
       0x591, 0x3, 0x2, 0x2, 0x2, 0x596, 0xb9, 0x3, 0x2, 0x2, 0x2, 0x597, 
       0x59b, 0x7, 0x37, 0x2, 0x2, 0x598, 0x59a, 0x7, 0x72, 0x2, 0x2, 0x599, 
       0x598, 0x3, 0x2, 0x2, 0x2, 0x59a, 0x59d, 0x3, 0x2, 0x2, 0x2, 0x59b, 
       0x599, 0x3, 0x2, 0x2, 0x2, 0x59b, 0x59c, 0x3, 0x2, 0x2, 0x2, 0x59c, 
       0x59e, 0x3, 0x2, 0x2, 0x2, 0x59d, 0x59b, 0x3, 0x2, 0x2, 0x2, 0x59e, 
       0x5a9, 0x5, 0x94, 0x4b, 0x2, 0x59f, 0x5a3, 0x7, 0x5e, 0x2, 0x2, 0x5a0, 
       0x5a2, 0x7, 0x72, 0x2, 0x2, 0x5a1, 0x5a0, 0x3, 0x2, 0x2, 0x2, 0x5a2, 
       0x5a5, 0x3, 0x2, 0x2, 0x2, 0x5a3, 0x5a1, 0x3, 0x2, 0x2, 0x2, 0x5a3, 
       0x5a4, 0x3, 0x2, 0x2, 0x2, 0x5a4, 0x5a6, 0x3, 0x2, 0x2, 0x2, 0x5a5, 
       0x5a3, 0x3, 0x2, 0x2, 0x2, 0x5a6, 0x5a8, 0x5, 0x94, 0x4b, 0x2, 0x5a7, 
       0x59f, 0x3, 0x2, 0x2, 0x2, 0x5a8, 0x5ab, 0x3, 0x2, 0x2, 0x2, 0x5a9, 
       0x5a7, 0x3, 0x2, 0x2, 0x2, 0x5a9, 0x5aa, 0x3, 0x2, 0x2, 0x2, 0x5aa, 
       0x5af, 0x3, 0x2, 0x2, 0x2, 0x5ab, 0x5a9, 0x3, 0x2, 0x2, 0x2, 0x5ac, 
       0x5ae, 0x7, 0x72, 0x2, 0x2, 0x5ad, 0x5ac, 0x3, 0x2, 0x2, 0x2, 0x5ae, 
       0x5b1, 0x3, 0x2, 0x2, 0x2, 0x5af, 0x5ad, 0x3, 0x2, 0x2, 0x2, 0x5af, 
       0x5b0, 0x3, 0x2, 0x2, 0x2, 0x5b0, 0x5b2, 0x3, 0x2, 0x2, 0x2, 0x5b1, 
       0x5af, 0x3, 0x2, 0x2, 0x2, 0x5b2, 0x5b3, 0x7, 0x38, 0x2, 0x2, 0x5b3, 
       0xbb, 0x3, 0x2, 0x2, 0x2, 0x5b4, 0x5b5, 0x9, 0xe, 0x2, 0x2, 0x5b5, 
       0xbd, 0x3, 0x2, 0x2, 0x2, 0x5b6, 0x5b8, 0xa, 0xf, 0x2, 0x2, 0x5b7, 
       0x5b6, 0x3, 0x2, 0x2, 0x2, 0x5b8, 0x5b9, 0x3, 0x2, 0x2, 0x2, 0x5b9, 
       0x5b7, 0x3, 0x2, 0x2, 0x2, 0x5b9, 0x5ba, 0x3, 0x2, 0x2, 0x2, 0x5ba, 
       0xbf, 0x3, 0x2, 0x2, 0x2, 0x5bb, 0x5bc, 0x7, 0x55, 0x2, 0x2, 0x5bc, 
       0x5bf, 0x7, 0x67, 0x2, 0x2, 0x5bd, 0x5bf, 0x5, 0x6a, 0x36, 0x2, 0x5be, 
       0x5bb, 0x3, 0x2, 0x2, 0x2, 0x5be, 0x5bd, 0x3, 0x2, 0x2, 0x2, 0x5bf, 
       0xc1, 0x3, 0x2, 0x2, 0x2, 0x5c0, 0x5c1, 0x7, 0x37, 0x2, 0x2, 0x5c1, 
       0x5c2, 0x5, 0x6a, 0x36, 0x2, 0x5c2, 0x5c3, 0x7, 0x5e, 0x2, 0x2, 0x5c3, 
       0x5c4, 0x5, 0x6a, 0x36, 0x2, 0x5c4, 0x5c5, 0x7, 0x38, 0x2, 0x2, 0x5c5, 
       0xc3, 0x3, 0x2, 0x2, 0x2, 0x5c6, 0x5cd, 0x7, 0x67, 0x2, 0x2, 0x5c7, 
       0x5c8, 0x7, 0x39, 0x2, 0x2, 0x5c8, 0x5c9, 0x5, 0x6a, 0x36, 0x2, 0x5c9, 
       0x5ca, 0x7, 0x3a, 0x2, 0x2, 0x5ca, 0x5cc, 0x3, 0x2, 0x2, 0x2, 0x5cb, 
       0x5c7, 0x3, 0x2, 0x2, 0x2, 0x5cc, 0x5cf, 0x3, 0x2, 0x2, 0x2, 0x5cd, 
       0x5cb, 0x3, 0x2, 0x2, 0x2, 0x5cd, 0x5ce, 0x3, 0x2, 0x2, 0x2, 0x5ce, 
       0x5d0, 0x3, 0x2, 0x2, 0x2, 0x5cf, 0x5cd, 0x3, 0x2, 0x2, 0x2, 0x5d0, 
       0x5d1, 0x9, 0x10, 0x2, 0x2, 0x5d1, 0xc5, 0x3, 0x2, 0x2, 0x2, 0x5d2, 
       0x5d4, 0x7, 0x67, 0x2, 0x2, 0x5d3, 0x5d2, 0x3, 0x2, 0x2, 0x2, 0x5d4, 
       0x5d5, 0x3, 0x2, 0x2, 0x2, 0x5d5, 0x5d3, 0x3, 0x2, 0x2, 0x2, 0x5d5, 
       0x5d6, 0x3, 0x2, 0x2, 0x2, 0x5d6, 0x5dd, 0x3, 0x2, 0x2, 0x2, 0x5d7, 
       0x5d8, 0x7, 0x39, 0x2, 0x2, 0x5d8, 0x5d9, 0x5, 0x6a, 0x36, 0x2, 0x5d9, 
       0x5da, 0x7, 0x3a, 0x2, 0x2, 0x5da, 0x5dc, 0x3, 0x2, 0x2, 0x2, 0x5db, 
       0x5d7, 0x3, 0x2, 0x2, 0x2, 0x5dc, 0x5df, 0x3, 0x2, 0x2, 0x2, 0x5dd, 
       0x5db, 0x3, 0x2, 0x2, 0x2, 0x5dd, 0x5de, 0x3, 0x2, 0x2, 0x2, 0x5de, 
       0x5e0, 0x3, 0x2, 0x2, 0x2, 0x5df, 0x5dd, 0x3, 0x2, 0x2, 0x2, 0x5e0, 
       0x5e1, 0x7, 0x55, 0x2, 0x2, 0x5e1, 0xc7, 0x3, 0x2, 0x2, 0x2, 0x5e2, 
       0x5e4, 0x5, 0xc6, 0x64, 0x2, 0x5e3, 0x5e2, 0x3, 0x2, 0x2, 0x2, 0x5e3, 
       0x5e4, 0x3, 0x2, 0x2, 0x2, 0x5e4, 0x5e8, 0x3, 0x2, 0x2, 0x2, 0x5e5, 
       0x5e7, 0x5, 0xc4, 0x63, 0x2, 0x5e6, 0x5e5, 0x3, 0x2, 0x2, 0x2, 0x5e7, 
       0x5ea, 0x3, 0x2, 0x2, 0x2, 0x5e8, 0x5e9, 0x3, 0x2, 0x2, 0x2, 0x5e8, 
       0x5e6, 0x3, 0x2, 0x2, 0x2, 0x5e9, 0x5eb, 0x3, 0x2, 0x2, 0x2, 0x5ea, 
       0x5e8, 0x3, 0x2, 0x2, 0x2, 0x5eb, 0x5ed, 0x7, 0x1f, 0x2, 0x2, 0x5ec, 
       0x5ee, 0x5, 0xc2, 0x62, 0x2, 0x5ed, 0x5ec, 0x3, 0x2, 0x2, 0x2, 0x5ed, 
       0x5ee, 0x3, 0x2, 0x2, 0x2, 0x5ee, 0x5f2, 0x3, 0x2, 0x2, 0x2, 0x5ef, 
       0x5f1, 0x5, 0xc4, 0x63, 0x2, 0x5f0, 0x5ef, 0x3, 0x2, 0x2, 0x2, 0x5f1, 
       0x5f4, 0x3, 0x2, 0x2, 0x2, 0x5f2, 0x5f3, 0x3, 0x2, 0x2, 0x2, 0x5f2, 
       0x5f0, 0x3, 0x2, 0x2, 0x2, 0x5f3, 0x5f5, 0x3, 0x2, 0x2, 0x2, 0x5f4, 
       0x5f2, 0x3, 0x2, 0x2, 0x2, 0x5f5, 0x5f6, 0x7, 0x67, 0x2, 0x2, 0x5f6, 
       0x5ff, 0x7, 0x37, 0x2, 0x2, 0x5f7, 0x5fc, 0x5, 0xc0, 0x61, 0x2, 0x5f8, 
       0x5f9, 0x7, 0x5e, 0x2, 0x2, 0x5f9, 0x5fb, 0x5, 0xc0, 0x61, 0x2, 0x5fa, 
       0x5f8, 0x3, 0x2, 0x2, 0x2, 0x5fb, 0x5fe, 0x3, 0x2, 0x2, 0x2, 0x5fc, 
       0x5fa, 0x3, 0x2, 0x2, 0x2, 0x5fc, 0x5fd, 0x3, 0x2, 0x2, 0x2, 0x5fd, 
       0x600, 0x3, 0x2, 0x2, 0x2, 0x5fe, 0x5fc, 0x3, 0x2, 0x2, 0x2, 0x5ff, 
       0x5f7, 0x3, 0x2, 0x2, 0x2, 0x5ff, 0x600, 0x3, 0x2, 0x2, 0x2, 0x600, 
       0x601, 0x3, 0x2, 0x2, 0x2, 0x601, 0x602, 0x7, 0x38, 0x2, 0x2, 0x602, 
       0x606, 0x7, 0x63, 0x2, 0x2, 0x603, 0x605, 0xa, 0xa, 0x2, 0x2, 0x604, 
       0x603, 0x3, 0x2, 0x2, 0x2, 0x605, 0x608, 0x3, 0x2, 0x2, 0x2, 0x606, 
       0x604, 0x3, 0x2, 0x2, 0x2, 0x606, 0x607, 0x3, 0x2, 0x2, 0x2, 0x607, 
       0x609, 0x3, 0x2, 0x2, 0x2, 0x608, 0x606, 0x3, 0x2, 0x2, 0x2, 0x609, 
       0x60a, 0x7, 0x72, 0x2, 0x2, 0x60a, 0xc9, 0x3, 0x2, 0x2, 0x2, 0x60b, 
       0x60d, 0x5, 0xc4, 0x63, 0x2, 0x60c, 0x60b, 0x3, 0x2, 0x2, 0x2, 0x60d, 
       0x610, 0x3, 0x2, 0x2, 0x2, 0x60e, 0x60f, 0x3, 0x2, 0x2, 0x2, 0x60e, 
       0x60c, 0x3, 0x2, 0x2, 0x2, 0x60f, 0x611, 0x3, 0x2, 0x2, 0x2, 0x610, 
       0x60e, 0x3, 0x2, 0x2, 0x2, 0x611, 0x617, 0x7, 0x20, 0x2, 0x2, 0x612, 
       0x614, 0x7, 0x37, 0x2, 0x2, 0x613, 0x615, 0x5, 0x6a, 0x36, 0x2, 0x614, 
       0x613, 0x3, 0x2, 0x2, 0x2, 0x614, 0x615, 0x3, 0x2, 0x2, 0x2, 0x615, 
       0x616, 0x3, 0x2, 0x2, 0x2, 0x616, 0x618, 0x7, 0x38, 0x2, 0x2, 0x617, 
       0x612, 0x3, 0x2, 0x2, 0x2, 0x617, 0x618, 0x3, 0x2, 0x2, 0x2, 0x618, 
       0x619, 0x3, 0x2, 0x2, 0x2, 0x619, 0x61d, 0x7, 0x63, 0x2, 0x2, 0x61a, 
       0x61c, 0xa, 0xa, 0x2, 0x2, 0x61b, 0x61a, 0x3, 0x2, 0x2, 0x2, 0x61c, 
       0x61f, 0x3, 0x2, 0x2, 0x2, 0x61d, 0x61b, 0x3, 0x2, 0x2, 0x2, 0x61d, 
       0x61e, 0x3, 0x2, 0x2, 0x2, 0x61e, 0x620, 0x3, 0x2, 0x2, 0x2, 0x61f, 
       0x61d, 0x3, 0x2, 0x2, 0x2, 0x620, 0x621, 0x7, 0x72, 0x2, 0x2, 0x621, 
       0xcb, 0x3, 0x2, 0x2, 0x2, 0x622, 0x626, 0x6, 0x67, 0x5, 0x2, 0x623, 
       0x625, 0xa, 0xa, 0x2, 0x2, 0x624, 0x623, 0x3, 0x2, 0x2, 0x2, 0x625, 
       0x628, 0x3, 0x2, 0x2, 0x2, 0x626, 0x624, 0x3, 0x2, 0x2, 0x2, 0x626, 
       0x627, 0x3, 0x2, 0x2, 0x2, 0x627, 0x629, 0x3, 0x2, 0x2, 0x2, 0x628, 
       0x626, 0x3, 0x2, 0x2, 0x2, 0x629, 0x62a, 0x7, 0x72, 0x2, 0x2, 0x62a, 
       0xcd, 0x3, 0x2, 0x2, 0x2, 0x62b, 0x62c, 0x9, 0x11, 0x2, 0x2, 0x62c, 
       0xcf, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xd1, 0xd9, 0xf8, 0xfd, 0x106, 0x10c, 
       0x116, 0x122, 0x125, 0x138, 0x13d, 0x13f, 0x145, 0x14c, 0x154, 0x15c, 
       0x164, 0x16c, 0x17e, 0x181, 0x183, 0x186, 0x18b, 0x18e, 0x194, 0x197, 
       0x19b, 0x1a2, 0x1a6, 0x1b1, 0x1bd, 0x1c0, 0x1c3, 0x1cc, 0x1d3, 0x1d7, 
       0x1dc, 0x1e0, 0x1e4, 0x1e8, 0x1ed, 0x1f1, 0x1f5, 0x1f9, 0x1fe, 0x202, 
       0x206, 0x20a, 0x20f, 0x213, 0x217, 0x21b, 0x220, 0x224, 0x231, 0x235, 
       0x239, 0x23d, 0x241, 0x244, 0x247, 0x24b, 0x24f, 0x253, 0x256, 0x259, 
       0x25d, 0x260, 0x264, 0x268, 0x26b, 0x26f, 0x274, 0x27b, 0x27d, 0x281, 
       0x285, 0x28b, 0x28f, 0x294, 0x298, 0x29f, 0x2a7, 0x2ac, 0x2b1, 0x2b9, 
       0x2c1, 0x2c3, 0x2c8, 0x2cc, 0x2cf, 0x2d5, 0x2e3, 0x2e8, 0x2f0, 0x2f8, 
       0x2fd, 0x301, 0x305, 0x30a, 0x30e, 0x311, 0x315, 0x319, 0x31e, 0x322, 
       0x325, 0x329, 0x32d, 0x331, 0x334, 0x338, 0x33a, 0x33f, 0x344, 0x348, 
       0x34c, 0x350, 0x355, 0x358, 0x35b, 0x35e, 0x360, 0x366, 0x36f, 0x373, 
       0x377, 0x37b, 0x37e, 0x381, 0x386, 0x393, 0x396, 0x39d, 0x3a4, 0x3ab, 
       0x3b2, 0x3b5, 0x3bb, 0x3be, 0x3cb, 0x3d0, 0x3d5, 0x3de, 0x3fb, 0x401, 
       0x408, 0x411, 0x414, 0x417, 0x41c, 0x426, 0x429, 0x42e, 0x431, 0x443, 
       0x445, 0x457, 0x45b, 0x46e, 0x47b, 0x47e, 0x485, 0x48c, 0x492, 0x49a, 
       0x49d, 0x4a2, 0x4a8, 0x4ab, 0x4b2, 0x4b7, 0x4be, 0x4cc, 0x4d0, 0x4da, 
       0x4e2, 0x4e6, 0x4ea, 0x4ee, 0x4f5, 0x4fb, 0x4fd, 0x504, 0x50a, 0x511, 
       0x518, 0x51e, 0x524, 0x528, 0x52f, 0x535, 0x53d, 0x542, 0x548, 0x550, 
       0x552, 0x55a, 0x560, 0x56c, 0x574, 0x579, 0x57b, 0x586, 0x589, 0x58c, 
       0x593, 0x595, 0x59b, 0x5a3, 0x5a9, 0x5af, 0x5b9, 0x5be, 0x5cd, 0x5d5, 
       0x5dd, 0x5e3, 0x5e8, 0x5ed, 0x5f2, 0x5fc, 0x5ff, 0x606, 0x60e, 0x614, 
       0x617, 0x61d, 0x626, 
  };

  _serializedATN.insert(_serializedATN.end(), serializedATNSegment0,
    serializedATNSegment0 + sizeof(serializedATNSegment0) / sizeof(serializedATNSegment0[0]));


  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ReentPreParser::Initializer ReentPreParser::_init;
