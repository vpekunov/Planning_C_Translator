
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
    setState(195);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(194);
      statementseq();
      break;
    }

    default:
      break;
    }
    setState(197);
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
    setState(201); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(200);
              statement();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(203); 
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
    setState(233);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(205);
      defModule();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(206);
      match(ReentPreParser::DefModule);

      		throw FailedPredicateException(this, "Something wrong with module definition");
      	
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(208);
      defMemoization();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(209);
      match(ReentPreParser::DefMemoization);

      		throw FailedPredicateException(this, "Something wrong with memoization");
      	
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(211);
      preprocPasses();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(212);
      match(ReentPreParser::PreprocPasses);

      		throw FailedPredicateException(this, "Something wrong with '#preproc_passes(n)'");
      	
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(214);
      addScan();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(215);
      match(ReentPreParser::AddScan);

      		throw FailedPredicateException(this, "Something wrong with '#add_scan'");
      	
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(217);
      scan();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(218);
      match(ReentPreParser::Scan);

      		throw FailedPredicateException(this, "Something wrong with '#scan'");
      	
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(220);
      addParse();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(221);
      match(ReentPreParser::AddParse);

      		throw FailedPredicateException(this, "Something wrong with '#add_parse'");
      	
      break;
    }

    case 13: {
      enterOuterAlt(_localctx, 13);
      setState(223);
      parse();
      break;
    }

    case 14: {
      enterOuterAlt(_localctx, 14);
      setState(224);
      match(ReentPreParser::Parse);

      		throw FailedPredicateException(this, "Something wrong with '#parse'");
      	
      break;
    }

    case 15: {
      enterOuterAlt(_localctx, 15);
      setState(226);
      def_pattern();
      break;
    }

    case 16: {
      enterOuterAlt(_localctx, 16);
      setState(227);
      match(ReentPreParser::DefPattern);

      		throw FailedPredicateException(this, "Something wrong with '#def_pattern'");
      	
      break;
    }

    case 17: {
      enterOuterAlt(_localctx, 17);
      setState(229);
      def_xpath();
      break;
    }

    case 18: {
      enterOuterAlt(_localctx, 18);
      setState(230);
      match(ReentPreParser::DefXPath);

      		throw FailedPredicateException(this, "Something wrong with '#def_xpath'");
      	
      break;
    }

    case 19: {
      enterOuterAlt(_localctx, 19);
      setState(232);
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
    setState(235);
    match(ReentPreParser::DefPattern);

    		regexp_vars.clear(); regexp_vars.insert("root");
    		regexp_refs.clear();
    		std::string call_macro;
    	
    setState(237);
    dynamic_cast<Def_patternContext *>(_localctx)->id = match(ReentPreParser::Identifier);

    		if (scanners.find((dynamic_cast<Def_patternContext *>(_localctx)->id != nullptr ? dynamic_cast<Def_patternContext *>(_localctx)->id->getText() : "")) != scanners.end())
    			throw FailedPredicateException(this, "Pattern is already defined");
    		scanners.insert((dynamic_cast<Def_patternContext *>(_localctx)->id != nullptr ? dynamic_cast<Def_patternContext *>(_localctx)->id->getText() : ""));
    	
    setState(239);
    match(ReentPreParser::AssignGreater);
    setState(243);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::LeftBracket: {
        setState(240);
        put_fact();
        break;
      }

      case ReentPreParser::Identifier: {
        setState(241);
        dynamic_cast<Def_patternContext *>(_localctx)->module = match(ReentPreParser::Identifier);

        				call_macro = (dynamic_cast<Def_patternContext *>(_localctx)->module != nullptr ? dynamic_cast<Def_patternContext *>(_localctx)->module->getText() : "");
        			
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(245);
    match(ReentPreParser::LeftParen);
     int param_count = 0; 
    setState(258);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(247);
      def_pattern_param();
       param_count++; 
      setState(255);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Comma) {
        setState(249);
        match(ReentPreParser::Comma);
        setState(250);
        def_pattern_param();
         param_count++; 
        setState(257);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    default:
      break;
    }
    setState(260);
    match(ReentPreParser::RightParen);

    		if (call_macro.length() > 0) {
    			if (module_refs.find(call_macro) != module_refs.end() && module_refs[call_macro] != param_count)
    				throw FailedPredicateException(this,
    					std::string("Pattern calls module '") + call_macro +
    					std::string("' with an incorrect number of params than in another patterns"));
    			else module_refs[call_macro] = param_count;
    		}
    	
    setState(262);
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
    setState(265);
    match(ReentPreParser::LeftBracket);
    setState(266);
    match(ReentPreParser::Identifier);
    setState(267);
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
    setState(290);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(269);
      match(ReentPreParser::CharacterLiteral);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(270);
      match(ReentPreParser::EmptyAtom);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(271);
      match(ReentPreParser::LeftBracket);
      setState(284);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
      case 1: {
        setState(272);
        def_pattern_param();
        setState(277);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ReentPreParser::Comma) {
          setState(273);
          match(ReentPreParser::Comma);
          setState(274);
          def_pattern_param();
          setState(279);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(282);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Or) {
          setState(280);
          match(ReentPreParser::Or);
          setState(281);
          def_pattern_param();
        }
        break;
      }

      default:
        break;
      }
      setState(286);
      match(ReentPreParser::RightBracket);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(287);
      simple_xpath_expression();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);

      		throw FailedPredicateException(this, "Unrecognized (prolog_fact/module)'s parameter");
      	
      setState(289);
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
    setState(292);
    xpath_and_expression();
    setState(297);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Or_) {
      setState(293);
      match(ReentPreParser::Or_);
      setState(294);
      xpath_and_expression();
      setState(299);
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
    setState(300);
    xpath_rel_expression();
    setState(305);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::And_) {
      setState(301);
      match(ReentPreParser::And_);
      setState(302);
      xpath_rel_expression();
      setState(307);
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
    setState(308);
    xpath_mul_expression();
    setState(313);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 81) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 81)) & ((1ULL << (ReentPreParser::Assign - 81))
      | (1ULL << (ReentPreParser::Less - 81))
      | (1ULL << (ReentPreParser::Greater - 81))
      | (1ULL << (ReentPreParser::NotEqual - 81))
      | (1ULL << (ReentPreParser::LessEqual - 81))
      | (1ULL << (ReentPreParser::GreaterEqual - 81)))) != 0)) {
      setState(309);
      _la = _input->LA(1);
      if (!(((((_la - 81) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 81)) & ((1ULL << (ReentPreParser::Assign - 81))
        | (1ULL << (ReentPreParser::Less - 81))
        | (1ULL << (ReentPreParser::Greater - 81))
        | (1ULL << (ReentPreParser::NotEqual - 81))
        | (1ULL << (ReentPreParser::LessEqual - 81))
        | (1ULL << (ReentPreParser::GreaterEqual - 81)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(310);
      xpath_mul_expression();
      setState(315);
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
    setState(316);
    xpath_plus_expression();
    setState(321);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Star

    || _la == ReentPreParser::Div) {
      setState(317);
      _la = _input->LA(1);
      if (!(_la == ReentPreParser::Star

      || _la == ReentPreParser::Div)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(318);
      xpath_plus_expression();
      setState(323);
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
    setState(324);
    xpath_unary_expression();
    setState(329);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Plus

    || _la == ReentPreParser::Minus) {
      setState(325);
      _la = _input->LA(1);
      if (!(_la == ReentPreParser::Plus

      || _la == ReentPreParser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(326);
      xpath_unary_expression();
      setState(331);
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
    setState(352);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(332);
      match(ReentPreParser::StringLiteral);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(333);
      match(ReentPreParser::CharacterLiteral);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(334);
      match(ReentPreParser::EmptyAtom);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(335);
      match(ReentPreParser::IntegerLiteral);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(336);
      match(ReentPreParser::FloatingLiteral);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(337);
      match(ReentPreParser::AtValue);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(338);
      match(ReentPreParser::GetText);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(339);
      match(ReentPreParser::LeftParen);
      setState(340);
      simple_xpath_expression();
      setState(341);
      match(ReentPreParser::RightParen);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(343);
      xpath_query();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(344);
      match(ReentPreParser::Identifier);
      setState(350);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::LeftParen) {
        setState(345);
        match(ReentPreParser::LeftParen);
        setState(347);
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
          | (1ULL << ReentPreParser::DivDiv))) != 0) || ((((_la - 73) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 73)) & ((1ULL << (ReentPreParser::Star - 73))
          | (1ULL << (ReentPreParser::Div - 73))
          | (1ULL << (ReentPreParser::Identifier - 73)))) != 0)) {
          setState(346);
          xpath_fun_params();
        }
        setState(349);
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
    setState(355);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::DivDiv

    || _la == ReentPreParser::Div) {
      setState(354);
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
    setState(360);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Identifier: {
        setState(357);
        dynamic_cast<Xpath_queryContext *>(_localctx)->var = match(ReentPreParser::Identifier);
         regexp_refs.insert((dynamic_cast<Xpath_queryContext *>(_localctx)->var != nullptr ? dynamic_cast<Xpath_queryContext *>(_localctx)->var->getText() : "")); 
        break;
      }

      case ReentPreParser::Star: {
        setState(359);
        match(ReentPreParser::Star);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(363);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftBracket) {
      setState(362);
      xpath_predicate();
    }
    setState(376);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(365);
        _la = _input->LA(1);
        if (!(_la == ReentPreParser::DivDiv

        || _la == ReentPreParser::Div)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(369);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case ReentPreParser::Identifier: {
            setState(366);
            dynamic_cast<Xpath_queryContext *>(_localctx)->next = match(ReentPreParser::Identifier);
             regexp_refs.insert((dynamic_cast<Xpath_queryContext *>(_localctx)->next != nullptr ? dynamic_cast<Xpath_queryContext *>(_localctx)->next->getText() : "")); 
            break;
          }

          case ReentPreParser::Star: {
            setState(368);
            match(ReentPreParser::Star);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(372);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::LeftBracket) {
          setState(371);
          xpath_predicate();
        } 
      }
      setState(378);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx);
    }
    setState(379);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::DivDiv

    || _la == ReentPreParser::Div)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(387);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Star:
      case ReentPreParser::Identifier: {
        setState(383);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case ReentPreParser::Identifier: {
            setState(380);
            dynamic_cast<Xpath_queryContext *>(_localctx)->last = match(ReentPreParser::Identifier);
             regexp_refs.insert((dynamic_cast<Xpath_queryContext *>(_localctx)->last != nullptr ? dynamic_cast<Xpath_queryContext *>(_localctx)->last->getText() : "")); 
            break;
          }

          case ReentPreParser::Star: {
            setState(382);
            match(ReentPreParser::Star);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

      case ReentPreParser::AtValue: {
        setState(385);
        match(ReentPreParser::AtValue);
        break;
      }

      case ReentPreParser::GetText: {
        setState(386);
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
    setState(389);
    match(ReentPreParser::LeftBracket);
    setState(390);
    simple_xpath_expression();
    setState(391);
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
    setState(393);
    simple_xpath_expression();
    setState(398);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(394);
      match(ReentPreParser::Comma);
      setState(395);
      simple_xpath_expression();
      setState(400);
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
    setState(401);
    match(ReentPreParser::DefXPath);
    setState(402);
    dynamic_cast<Def_xpathContext *>(_localctx)->id = match(ReentPreParser::Identifier);

    		if (xpaths.find((dynamic_cast<Def_xpathContext *>(_localctx)->id != nullptr ? dynamic_cast<Def_xpathContext *>(_localctx)->id->getText() : "")) != xpaths.end())
    			throw FailedPredicateException(this, "XPath is already defined");
    		xpaths.insert((dynamic_cast<Def_xpathContext *>(_localctx)->id != nullptr ? dynamic_cast<Def_xpathContext *>(_localctx)->id->getText() : ""));
    	
    setState(416);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftParen) {
      setState(404);
      match(ReentPreParser::LeftParen);
      setState(413);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Regexp_ref

      || _la == ReentPreParser::And) {
        setState(405);
        def_xpath_param();
        setState(410);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ReentPreParser::Comma) {
          setState(406);
          match(ReentPreParser::Comma);
          setState(407);
          def_xpath_param();
          setState(412);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(415);
      match(ReentPreParser::RightParen);
    }
    setState(418);
    match(ReentPreParser::LeftBrace);
    setState(419);
    match(ReentPreParser::Newline);
    setState(420);
    def_xpath_expression();
    setState(421);
    match(ReentPreParser::RightBrace);
    setState(422);
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
    setState(425);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::And) {
      setState(424);
      match(ReentPreParser::And);
    }
    setState(427);
    match(ReentPreParser::Regexp_ref);
    setState(428);
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
    setState(430);
    def_xpath_and_expression();
    setState(441);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(432);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(431);
          match(ReentPreParser::Newline);
        }
        setState(434);
        match(ReentPreParser::Or_);
        setState(436);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          setState(435);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(438);
        def_xpath_and_expression(); 
      }
      setState(443);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
    setState(445);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      setState(444);
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
    setState(447);
    def_xpath_rel_expression();
    setState(458);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(449);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(448);
          match(ReentPreParser::Newline);
        }
        setState(451);
        match(ReentPreParser::And_);
        setState(453);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx)) {
        case 1: {
          setState(452);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(455);
        def_xpath_rel_expression(); 
      }
      setState(460);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    }
    setState(462);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      setState(461);
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
    setState(464);
    def_xpath_mul_expression();
    setState(475);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(466);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(465);
          match(ReentPreParser::Newline);
        }
        setState(468);
        _la = _input->LA(1);
        if (!(((((_la - 81) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 81)) & ((1ULL << (ReentPreParser::Assign - 81))
          | (1ULL << (ReentPreParser::Less - 81))
          | (1ULL << (ReentPreParser::Greater - 81))
          | (1ULL << (ReentPreParser::NotEqual - 81))
          | (1ULL << (ReentPreParser::LessEqual - 81))
          | (1ULL << (ReentPreParser::GreaterEqual - 81)))) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(470);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
        case 1: {
          setState(469);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(472);
        def_xpath_mul_expression(); 
      }
      setState(477);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    }
    setState(479);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      setState(478);
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
    setState(481);
    def_xpath_plus_expression();
    setState(492);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(483);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(482);
          match(ReentPreParser::Newline);
        }
        setState(485);
        _la = _input->LA(1);
        if (!(_la == ReentPreParser::Star

        || _la == ReentPreParser::Div)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(487);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
        case 1: {
          setState(486);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(489);
        def_xpath_plus_expression(); 
      }
      setState(494);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    }
    setState(496);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
    case 1: {
      setState(495);
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
    setState(498);
    def_xpath_unary_expression();
    setState(509);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(500);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(499);
          match(ReentPreParser::Newline);
        }
        setState(502);
        _la = _input->LA(1);
        if (!(_la == ReentPreParser::Plus

        || _la == ReentPreParser::Minus)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(504);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
        case 1: {
          setState(503);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(506);
        def_xpath_unary_expression(); 
      }
      setState(511);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 49, _ctx);
    }
    setState(513);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 50, _ctx)) {
    case 1: {
      setState(512);
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
    setState(560);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(515);
      match(ReentPreParser::StringLiteral);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(516);
      match(ReentPreParser::CharacterLiteral);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(517);
      match(ReentPreParser::EmptyAtom);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(518);
      match(ReentPreParser::IntegerLiteral);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(519);
      match(ReentPreParser::FloatingLiteral);
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(520);
      match(ReentPreParser::AtValue);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(521);
      match(ReentPreParser::At);
      setState(522);
      match(ReentPreParser::Identifier);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(523);
      match(ReentPreParser::GetText);
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(524);
      match(ReentPreParser::LeftParen);
      setState(526);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
      case 1: {
        setState(525);
        match(ReentPreParser::Newline);
        break;
      }

      default:
        break;
      }
      setState(528);
      def_xpath_expression();
      setState(530);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(529);
        match(ReentPreParser::Newline);
      }
      setState(532);
      match(ReentPreParser::RightParen);
      setState(534);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx)) {
      case 1: {
        setState(533);
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
      setState(536);
      match(ReentPreParser::Identifier);
      setState(538);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(537);
        match(ReentPreParser::Newline);
      }
      setState(540);
      match(ReentPreParser::LeftParen);
      setState(542);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 55, _ctx)) {
      case 1: {
        setState(541);
        match(ReentPreParser::Newline);
        break;
      }

      default:
        break;
      }
      setState(545);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx)) {
      case 1: {
        setState(544);
        def_xpath_fun_params();
        break;
      }

      default:
        break;
      }
      setState(548);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(547);
        match(ReentPreParser::Newline);
      }
      setState(550);
      match(ReentPreParser::RightParen);
      setState(552);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 58, _ctx)) {
      case 1: {
        setState(551);
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
      setState(554);
      def_xpath_query();
      setState(556);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
      case 1: {
        setState(555);
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
      setState(558);
      match(ReentPreParser::Regexp_ref);
      setState(559);
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
    setState(563);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::DivDiv

    || _la == ReentPreParser::Div) {
      setState(562);
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
    setState(566);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Newline) {
      setState(565);
      match(ReentPreParser::Newline);
    }
    setState(568);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::Star

    || _la == ReentPreParser::Identifier)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(570);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      setState(569);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(573);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftBracket) {
      setState(572);
      def_xpath_predicate();
    }
    setState(588);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(575);
        _la = _input->LA(1);
        if (!(_la == ReentPreParser::DivDiv

        || _la == ReentPreParser::Div)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(577);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(576);
          match(ReentPreParser::Newline);
        }
        setState(579);
        _la = _input->LA(1);
        if (!(_la == ReentPreParser::Star

        || _la == ReentPreParser::Identifier)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(581);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx)) {
        case 1: {
          setState(580);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(584);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::LeftBracket) {
          setState(583);
          def_xpath_predicate();
        } 
      }
      setState(590);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx);
    }
    setState(602);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx)) {
    case 1: {
      setState(591);
      _la = _input->LA(1);
      if (!(_la == ReentPreParser::DivDiv

      || _la == ReentPreParser::Div)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(593);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(592);
        match(ReentPreParser::Newline);
      }
      setState(600);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case ReentPreParser::Star:
        case ReentPreParser::Identifier: {
          setState(595);
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
          setState(596);
          match(ReentPreParser::AtValue);
          break;
        }

        case ReentPreParser::At: {
          setState(597);
          match(ReentPreParser::At);
          setState(598);
          match(ReentPreParser::Identifier);
          break;
        }

        case ReentPreParser::GetText: {
          setState(599);
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
    setState(604);
    match(ReentPreParser::LeftBracket);
    setState(606);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      setState(605);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(608);
    def_xpath_expression();
    setState(610);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Newline) {
      setState(609);
      match(ReentPreParser::Newline);
    }
    setState(612);
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
    setState(614);
    def_xpath_expression();
    setState(625);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(616);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(615);
          match(ReentPreParser::Newline);
        }
        setState(618);
        match(ReentPreParser::Comma);
        setState(620);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx)) {
        case 1: {
          setState(619);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(622);
        def_xpath_expression(); 
      }
      setState(627);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx);
    }
    setState(629);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 77, _ctx)) {
    case 1: {
      setState(628);
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
    setState(631);
    match(ReentPreParser::LeftBrace);
    setState(632);
    match(ReentPreParser::Newline);
    setState(636);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(633);
        regexp_lines(); 
      }
      setState(638);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 78, _ctx);
    }
    setState(649);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 80, _ctx)) {
    case 1: {
      setState(639);
      match(ReentPreParser::Regexp_begin);
      setState(640);
      match(ReentPreParser::Newline);
      setState(644);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(641);
          regexp_lines(); 
        }
        setState(646);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
      }
      setState(647);
      match(ReentPreParser::Regexp_end);
      setState(648);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(654);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(651);
        regexp_lines(); 
      }
      setState(656);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 81, _ctx);
    }
    setState(657);
    match(ReentPreParser::RightBrace);
    setState(658);
    match(ReentPreParser::Semi);
    setState(659);
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
    setState(662);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx)) {
    case 1: {
      setState(661);
      regexp_body();
      break;
    }

    default:
      break;
    }
    setState(664);
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
    setState(666);

    if (!(
    		!_input->LT(-1) || _input->LT(-1)->getText()!="\n" ||
    		(_input->LT(1) && _input->LT(1)->getText() != "@begin" && _input->LT(1)->getText() != "@end" &&
    		 (_input->LT(1)->getText() != "}" || _input->LT(2) && _input->LT(2)->getText() != ";"))
    	)) throw FailedPredicateException(this, "\n\t\t!_input->LT(-1) || _input->LT(-1)->getText()!=\"\\n\" ||\n\t\t(_input->LT(1) && _input->LT(1)->getText() != \"@begin\" && _input->LT(1)->getText() != \"@end\" &&\n\t\t (_input->LT(1)->getText() != \"}\" || _input->LT(2) && _input->LT(2)->getText() != \";\"))\n\t");
    setState(681);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::LeftParen: {
        setState(667);
        match(ReentPreParser::LeftParen);
        setState(672);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(670);
            _errHandler->sync(this);
            switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 83, _ctx)) {
            case 1: {
              setState(668);
              regexp_body();
              break;
            }

            case 2: {
              setState(669);
              match(ReentPreParser::Newline);
              break;
            }

            default:
              break;
            } 
          }
          setState(674);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx);
        }
        setState(677);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case ReentPreParser::Plc_regexp_var:
          case ReentPreParser::Plc_regexp_equal:
          case ReentPreParser::Plc_regexp_not_equal:
          case ReentPreParser::Plc_regexp_query: {
            setState(675);
            plc_regexp_logical();
            break;
          }

          case ReentPreParser::RightParen: {
            setState(676);
            match(ReentPreParser::RightParen);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

      case ReentPreParser::Regexp_set: {
        setState(679);
        match(ReentPreParser::Regexp_set);
        break;
      }

      case ReentPreParser::Regexp_fragment: {
        setState(680);
        match(ReentPreParser::Regexp_fragment);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(684);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 87, _ctx)) {
    case 1: {
      setState(683);
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
    setState(690);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Plc_regexp_var: {
        enterOuterAlt(_localctx, 1);
        setState(686);
        plc_regexp_var();
        break;
      }

      case ReentPreParser::Plc_regexp_equal: {
        enterOuterAlt(_localctx, 2);
        setState(687);
        plc_regexp_equal();
        break;
      }

      case ReentPreParser::Plc_regexp_not_equal: {
        enterOuterAlt(_localctx, 3);
        setState(688);
        plc_regexp_not_equal();
        break;
      }

      case ReentPreParser::Plc_regexp_query: {
        enterOuterAlt(_localctx, 4);
        setState(689);
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
    setState(692);
    match(ReentPreParser::Plc_regexp_var);

    setState(693);
    dynamic_cast<Plc_regexp_varContext *>(_localctx)->lib_or_id = match(ReentPreParser::Identifier);
    setState(704);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 89, _ctx)) {
    case 1: {
      setState(694);
      match(ReentPreParser::Dot);
      setState(695);
      match(ReentPreParser::Identifier);
      setState(696);
      match(ReentPreParser::LeftBrace);
      setState(697);
      dynamic_cast<Plc_regexp_varContext *>(_localctx)->var = match(ReentPreParser::Identifier);
      setState(698);
      match(ReentPreParser::RightBrace);
      setState(699);
      match(ReentPreParser::RightBrace);
       regexp_vars.insert((dynamic_cast<Plc_regexp_varContext *>(_localctx)->var != nullptr ? dynamic_cast<Plc_regexp_varContext *>(_localctx)->var->getText() : "")); 
      break;
    }

    case 2: {
      setState(701);
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
    setState(706);
    match(ReentPreParser::Plc_regexp_equal);
    setState(709);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Identifier: {
        setState(707);
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
    setState(711);
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
    setState(714);
    match(ReentPreParser::Plc_regexp_not_equal);
    setState(717);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Identifier: {
        setState(715);
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
    setState(719);
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
    setState(722);
    match(ReentPreParser::Plc_regexp_query);
    setState(725);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Regexp_parallel:
      case ReentPreParser::Regexp_sequential:
      case ReentPreParser::LeftParen:
      case ReentPreParser::Not:
      case ReentPreParser::Identifier:
      case ReentPreParser::Newline: {
        setState(723);
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
    setState(727);
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
    setState(730);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 93, _ctx)) {
    case 1: {
      setState(729);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(732);
    regexp_and_sequence();
    setState(743);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(734);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(733);
          match(ReentPreParser::Newline);
        }
        setState(736);
        match(ReentPreParser::Semi);
        setState(738);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 95, _ctx)) {
        case 1: {
          setState(737);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(740);
        regexp_and_sequence(); 
      }
      setState(745);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 96, _ctx);
    }
    setState(747);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 97, _ctx)) {
    case 1: {
      setState(746);
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
    setState(750);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx)) {
    case 1: {
      setState(749);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(752);
    regexp_unary();
    setState(763);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 101, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(754);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Newline) {
          setState(753);
          match(ReentPreParser::Newline);
        }
        setState(756);
        match(ReentPreParser::Comma);
        setState(758);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx)) {
        case 1: {
          setState(757);
          match(ReentPreParser::Newline);
          break;
        }

        default:
          break;
        }
        setState(760);
        regexp_unary(); 
      }
      setState(765);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 101, _ctx);
    }
    setState(767);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 102, _ctx)) {
    case 1: {
      setState(766);
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
    setState(791);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 109, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(770);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(769);
        match(ReentPreParser::Newline);
      }
      setState(772);
      match(ReentPreParser::LeftParen);
      setState(774);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 104, _ctx)) {
      case 1: {
        setState(773);
        match(ReentPreParser::Newline);
        break;
      }

      default:
        break;
      }
      setState(776);
      regexp_or_sequence();
      setState(778);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(777);
        match(ReentPreParser::Newline);
      }
      setState(780);
      match(ReentPreParser::RightParen);
      setState(782);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 106, _ctx)) {
      case 1: {
        setState(781);
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
      setState(785);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(784);
        match(ReentPreParser::Newline);
      }
      setState(787);
      regexp_pred();
      setState(789);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 108, _ctx)) {
      case 1: {
        setState(788);
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
    setState(829);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Regexp_parallel: {
        enterOuterAlt(_localctx, 1);
        setState(793);
        regexp_pred_parallel();
        break;
      }

      case ReentPreParser::Regexp_sequential: {
        enterOuterAlt(_localctx, 2);
        setState(794);
        match(ReentPreParser::Regexp_sequential);
        break;
      }

      case ReentPreParser::Not:
      case ReentPreParser::Identifier: {
        enterOuterAlt(_localctx, 3);
        setState(796);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Not) {
          setState(795);
          match(ReentPreParser::Not);
        }
        setState(798);
        match(ReentPreParser::Identifier);
        setState(801);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Dot) {
          setState(799);
          match(ReentPreParser::Dot);
          setState(800);
          match(ReentPreParser::Identifier);
        }
        setState(827);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::LeftParen) {
          setState(803);
          match(ReentPreParser::LeftParen);
          setState(821);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 116, _ctx)) {
          case 1: {
            setState(805);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == ReentPreParser::Newline) {
              setState(804);
              match(ReentPreParser::Newline);
            }
            setState(807);
            regexp_pred_arg();
            setState(818);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 115, _ctx);
            while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
              if (alt == 1) {
                setState(809);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == ReentPreParser::Newline) {
                  setState(808);
                  match(ReentPreParser::Newline);
                }
                setState(811);
                match(ReentPreParser::Comma);
                setState(813);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == ReentPreParser::Newline) {
                  setState(812);
                  match(ReentPreParser::Newline);
                }
                setState(815);
                regexp_pred_arg(); 
              }
              setState(820);
              _errHandler->sync(this);
              alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 115, _ctx);
            }
            break;
          }

          default:
            break;
          }
          setState(824);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == ReentPreParser::Newline) {
            setState(823);
            match(ReentPreParser::Newline);
          }
          setState(826);
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
    setState(844);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Underscore: {
        enterOuterAlt(_localctx, 1);
        setState(831);
        match(ReentPreParser::Underscore);
        break;
      }

      case ReentPreParser::Regexp_ref: {
        enterOuterAlt(_localctx, 2);
        setState(832);
        match(ReentPreParser::Regexp_ref);
        setState(835);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Identifier) {
          setState(833);
          dynamic_cast<Regexp_pred_argContext *>(_localctx)->ref = match(ReentPreParser::Identifier);
           regexp_refs.insert((dynamic_cast<Regexp_pred_argContext *>(_localctx)->ref != nullptr ? dynamic_cast<Regexp_pred_argContext *>(_localctx)->ref->getText() : "")); 
        }
        break;
      }

      case ReentPreParser::StringLiteral: {
        enterOuterAlt(_localctx, 3);
        setState(837);
        match(ReentPreParser::StringLiteral);
        break;
      }

      case ReentPreParser::CharacterLiteral: {
        enterOuterAlt(_localctx, 4);
        setState(838);
        match(ReentPreParser::CharacterLiteral);
        break;
      }

      case ReentPreParser::EmptyAtom: {
        enterOuterAlt(_localctx, 5);
        setState(839);
        match(ReentPreParser::EmptyAtom);
        break;
      }

      case ReentPreParser::IntegerLiteral: {
        enterOuterAlt(_localctx, 6);
        setState(840);
        match(ReentPreParser::IntegerLiteral);
        break;
      }

      case ReentPreParser::FloatingLiteral: {
        enterOuterAlt(_localctx, 7);
        setState(841);
        match(ReentPreParser::FloatingLiteral);
        break;
      }

      case ReentPreParser::Identifier: {
        enterOuterAlt(_localctx, 8);
        setState(842);
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
    setState(846);
    match(ReentPreParser::Regexp_parallel);
    setState(848);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 122, _ctx)) {
    case 1: {
      setState(847);
      match(ReentPreParser::Newline);
      break;
    }

    default:
      break;
    }
    setState(859);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftParen) {
      setState(850);
      match(ReentPreParser::LeftParen);
      setState(852);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(851);
        match(ReentPreParser::Newline);
      }
      setState(854);
      match(ReentPreParser::Regexp_analyze);
      setState(856);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Newline) {
        setState(855);
        match(ReentPreParser::Newline);
      }
      setState(858);
      match(ReentPreParser::RightParen);
    }
    setState(862);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 126, _ctx)) {
    case 1: {
      setState(861);
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
    setState(864);
    match(ReentPreParser::DefModule);
    setState(865);
    match(ReentPreParser::LeftParen);
    setState(867);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Identifier) {
      setState(866);
      match(ReentPreParser::Identifier);
    }
    setState(869);
    match(ReentPreParser::RightParen);
    setState(870);
    dynamic_cast<DefModuleContext *>(_localctx)->ident = match(ReentPreParser::Identifier);
    setState(871);
    match(ReentPreParser::LeftParen);
     int param_counter = 0; 
    setState(883);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Identifier) {
      setState(873);
      match(ReentPreParser::Identifier);
       param_counter++; 
      setState(880);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Comma) {
        setState(875);
        match(ReentPreParser::Comma);
        setState(876);
        match(ReentPreParser::Identifier);
         param_counter++; 
        setState(882);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(885);
    match(ReentPreParser::RightParen);

    		modules[(dynamic_cast<DefModuleContext *>(_localctx)->ident != nullptr ? dynamic_cast<DefModuleContext *>(_localctx)->ident->getText() : "")] = param_counter;
    	
    setState(890);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(887);
      match(ReentPreParser::Newline);
      setState(892);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(893);
    match(ReentPreParser::LeftBrace);
    setState(897);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 131, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(894);
        match(ReentPreParser::Newline); 
      }
      setState(899);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 131, _ctx);
    }
    setState(900);
    defModuleDescriptors();
    setState(904);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 132, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(901);
        match(ReentPreParser::Newline); 
      }
      setState(906);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 132, _ctx);
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

std::vector<ReentPreParser::DefModuleDescriptorContext *> ReentPreParser::DefModuleDescriptorsContext::defModuleDescriptor() {
  return getRuleContexts<ReentPreParser::DefModuleDescriptorContext>();
}

ReentPreParser::DefModuleDescriptorContext* ReentPreParser::DefModuleDescriptorsContext::defModuleDescriptor(size_t i) {
  return getRuleContext<ReentPreParser::DefModuleDescriptorContext>(i);
}

tree::TerminalNode* ReentPreParser::DefModuleDescriptorsContext::RightBrace() {
  return getToken(ReentPreParser::RightBrace, 0);
}

tree::TerminalNode* ReentPreParser::DefModuleDescriptorsContext::Semi() {
  return getToken(ReentPreParser::Semi, 0);
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

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(907);
    defModuleDescriptor();
    setState(911);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::RightBrace: {
        setState(908);
        match(ReentPreParser::RightBrace);
        setState(909);
        match(ReentPreParser::Semi);
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
        setState(910);
        defModuleDescriptor();
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
    setState(920);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::At: {
        enterOuterAlt(_localctx, 1);
        setState(913);
        match(ReentPreParser::At);
        setState(917);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 134, _ctx)) {
        case 1: {
          setState(914);
          prolog_goal();
          break;
        }

        case 2: {
          setState(915);
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
        setState(919);
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
    setState(922);
    match(ReentPreParser::DefMemoization);
    setState(923);
    match(ReentPreParser::LeftParen);
     memo_map.clear(); int param_counter = 0; 
    setState(925);
    dynamic_cast<DefMemoizationContext *>(_localctx)->first = memoMapItem();
     param_counter++; memo_map.push_back((dynamic_cast<DefMemoizationContext *>(_localctx)->first != nullptr ? _input->getText(dynamic_cast<DefMemoizationContext *>(_localctx)->first->start, dynamic_cast<DefMemoizationContext *>(_localctx)->first->stop) : nullptr)); 
    setState(933);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(927);
      match(ReentPreParser::Comma);
      setState(928);
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
      	
      setState(935);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(936);
    match(ReentPreParser::RightParen);
    setState(938);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ReentPreParser::Feed_forward)
      | (1ULL << ReentPreParser::Lin_extrapolator)
      | (1ULL << ReentPreParser::Mgua))) != 0)) {
      setState(937);
      memoizationStyle();
    }
    setState(941); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(940);
      match(ReentPreParser::Newline);
      setState(943); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ReentPreParser::Newline);
    setState(945);
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
    setState(947);
    match(ReentPreParser::PreprocPasses);
    setState(948);
    match(ReentPreParser::LeftParen);
    setState(949);
    match(ReentPreParser::IntegerLiteral);
    setState(952);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Comma) {
      setState(950);
      match(ReentPreParser::Comma);
      setState(951);
      match(ReentPreParser::StringLiteral);
    }
    setState(954);
    match(ReentPreParser::RightParen);
    setState(955);
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
    setState(957);
    match(ReentPreParser::AddScan);
    setState(958);
    scanners_list();
    setState(959);
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
    setState(961);
    match(ReentPreParser::Scan);
    setState(962);
    scanners_list();
    setState(963);
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
    setState(965);
    match(ReentPreParser::AddParse);
    setState(966);
    scanners_list();
    setState(967);
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
    setState(969);
    match(ReentPreParser::Parse);
    setState(970);
    scanners_list();
    setState(971);
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
    setState(973);
    match(ReentPreParser::LeftParen);
    setState(974);
    dynamic_cast<Scanners_listContext *>(_localctx)->first = match(ReentPreParser::Identifier);

    			scanner_refs.insert((dynamic_cast<Scanners_listContext *>(_localctx)->first != nullptr ? dynamic_cast<Scanners_listContext *>(_localctx)->first->getText() : ""));
    		
    setState(981);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(976);
      match(ReentPreParser::Comma);
      setState(977);
      dynamic_cast<Scanners_listContext *>(_localctx)->next = match(ReentPreParser::Identifier);

      			scanner_refs.insert((dynamic_cast<Scanners_listContext *>(_localctx)->next != nullptr ? dynamic_cast<Scanners_listContext *>(_localctx)->next->getText() : ""));
      		
      setState(983);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(984);
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
    setState(987);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 141, _ctx)) {
    case 1: {
      setState(986);
      match(ReentPreParser::Star);
      break;
    }

    default:
      break;
    }
    setState(989);
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
    setState(994);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 142, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(991);

      if (!( _input->LT(1)->getText() == "i" || _input->LT(1)->getText() == "o" ||
      	  _input->LT(1)->getText() == "g" || _input->LT(1)->getText() == "t" )) throw FailedPredicateException(this, " _input->LT(1)->getText() == \"i\" || _input->LT(1)->getText() == \"o\" ||\n\t  _input->LT(1)->getText() == \"g\" || _input->LT(1)->getText() == \"t\" ");
      setState(992);
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

std::vector<ReentPreParser::Cpp_balanced_expressionContext *> ReentPreParser::Cpp_balanced_expressionContext::cpp_balanced_expression() {
  return getRuleContexts<ReentPreParser::Cpp_balanced_expressionContext>();
}

ReentPreParser::Cpp_balanced_expressionContext* ReentPreParser::Cpp_balanced_expressionContext::cpp_balanced_expression(size_t i) {
  return getRuleContext<ReentPreParser::Cpp_balanced_expressionContext>(i);
}

std::vector<tree::TerminalNode *> ReentPreParser::Cpp_balanced_expressionContext::LeftParen() {
  return getTokens(ReentPreParser::LeftParen);
}

tree::TerminalNode* ReentPreParser::Cpp_balanced_expressionContext::LeftParen(size_t i) {
  return getToken(ReentPreParser::LeftParen, i);
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
    setState(1009);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
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
        setState(997); 
        _errHandler->sync(this);
        alt = 1;
        do {
          switch (alt) {
            case 1: {
                  setState(996);
                  _la = _input->LA(1);
                  if (_la == 0 || _la == Token::EOF || (((((_la - 51) & ~ 0x3fULL) == 0) &&
                    ((1ULL << (_la - 51)) & ((1ULL << (ReentPreParser::LeftParen - 51))
                    | (1ULL << (ReentPreParser::RightParen - 51))
                    | (1ULL << (ReentPreParser::LeftBracket - 51))
                    | (1ULL << (ReentPreParser::RightBracket - 51))
                    | (1ULL << (ReentPreParser::Comma - 51)))) != 0))) {
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
          setState(999); 
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 143, _ctx);
        } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
        break;
      }

      case ReentPreParser::LeftParen: {
        setState(1001);
        match(ReentPreParser::LeftParen);
        setState(1002);
        cpp_balanced_expression();
        setState(1003);
        match(ReentPreParser::RightParen);
        break;
      }

      case ReentPreParser::LeftBracket: {
        setState(1005);
        match(ReentPreParser::LeftBracket);
        setState(1006);
        cpp_balanced_expression();
        setState(1007);
        match(ReentPreParser::RightBracket);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(1011);
    cpp_balanced_expression();
   
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
    setState(1016);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Mgua: {
        setState(1013);
        mgua();
        break;
      }

      case ReentPreParser::Feed_forward: {
        setState(1014);
        nnet();
        break;
      }

      case ReentPreParser::Lin_extrapolator: {
        setState(1015);
        extrapolator();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(1019);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Conditions

    || _la == ReentPreParser::Controlled) {
      setState(1018);
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
    setState(1021);
    match(ReentPreParser::Mgua);
    setState(1022);
    match(ReentPreParser::LeftParen);
    setState(1023);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::IntegerLiteral

    || _la == ReentPreParser::FloatingLiteral || _la == ReentPreParser::Identifier)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(1024);
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
    setState(1026);
    match(ReentPreParser::Feed_forward);
    setState(1027);
    match(ReentPreParser::LeftParen);
    setState(1028);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::IntegerLiteral

    || _la == ReentPreParser::FloatingLiteral)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(1029);
    match(ReentPreParser::Comma);

    setState(1030);
    match(ReentPreParser::FloatingLiteral);
    setState(1031);
    match(ReentPreParser::Comma);

    setState(1032);
    match(ReentPreParser::IntegerLiteral);
    setState(1039);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Comma) {
      setState(1033);
      match(ReentPreParser::Comma);
      setState(1034);
      nnet_layer_specifier();
      setState(1037);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Comma) {
        setState(1035);
        match(ReentPreParser::Comma);
        setState(1036);
        nnet_layer_specifier();
      }
    }
    setState(1041);
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
    setState(1043);
    match(ReentPreParser::Lin_extrapolator);
    setState(1044);
    match(ReentPreParser::LeftParen);
    setState(1045);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::IntegerLiteral

    || _la == ReentPreParser::FloatingLiteral)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(1046);
    match(ReentPreParser::Comma);
    setState(1047);
    match(ReentPreParser::IntegerLiteral);
    setState(1048);
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
    setState(1050);
    match(ReentPreParser::IntegerLiteral);
    setState(1051);
    match(ReentPreParser::Comma);
    setState(1052);
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
    setState(1057);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 149, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1054);

      if (!( _input->LT(1)->getText() == "e" || _input->LT(1)->getText() == "l" ||
      	  _input->LT(1)->getText() == "h" || _input->LT(1)->getText() == "r" )) throw FailedPredicateException(this, " _input->LT(1)->getText() == \"e\" || _input->LT(1)->getText() == \"l\" ||\n\t  _input->LT(1)->getText() == \"h\" || _input->LT(1)->getText() == \"r\" ");
      setState(1055);
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
    setState(1061);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Controlled: {
        enterOuterAlt(_localctx, 1);
        setState(1059);
        automated_control();
        break;
      }

      case ReentPreParser::Conditions: {
        enterOuterAlt(_localctx, 2);
        setState(1060);
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
    setState(1063);
    match(ReentPreParser::Controlled);
    setState(1064);
    match(ReentPreParser::LeftParen);
    setState(1065);
    match(ReentPreParser::IntegerLiteral);
    setState(1066);
    match(ReentPreParser::Comma);
    setState(1067);
    match(ReentPreParser::IntegerLiteral);
    setState(1068);
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
    setState(1070);
    match(ReentPreParser::Conditions);
    setState(1071);
    match(ReentPreParser::LeftParen);
    setState(1072);
    cpp_balanced_expression();
    setState(1073);
    match(ReentPreParser::Comma);
    setState(1074);
    cpp_balanced_expression();
    setState(1075);
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
    setState(1078); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(1077);
              dynamic_cast<BlockHeaderContext *>(_localctx)->type = typeItem();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(1080); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 151, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(1082);
    match(ReentPreParser::Identifier);
    setState(1083);
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
    	
    setState(1096);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Identifier) {
      setState(1085);
      parameter();
       param_count++; 
      setState(1093);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Comma) {
        setState(1087);
        match(ReentPreParser::Comma);
        setState(1088);
        parameter();
         param_count++; 
        setState(1095);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(1098);
    match(ReentPreParser::RightParen);
     if (param_count != memo_map.size()) throw FailedPredicateException(this, "number of mapping parameters does not correspond to the number of parameters in function's header"); 
    setState(1103);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(1100);
      match(ReentPreParser::Newline);
      setState(1105);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1106);
    match(ReentPreParser::LeftBrace);
    setState(1110);
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
      | (1ULL << ReentPreParser::Or_)
      | (1ULL << ReentPreParser::At)
      | (1ULL << ReentPreParser::Is))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (ReentPreParser::Is_ - 64))
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
      setState(1107);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == ReentPreParser::Newline)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1112);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1114); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(1113);
              match(ReentPreParser::Newline);
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(1116); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 156, _ctx);
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
    setState(1118);
    typeSpecifier();
    setState(1127);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::And: {
        setState(1119);
        match(ReentPreParser::And);
        break;
      }

      case ReentPreParser::AndAnd: {
        setState(1120);
        match(ReentPreParser::AndAnd);
        break;
      }

      case ReentPreParser::Star:
      case ReentPreParser::Identifier: {
        setState(1124);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ReentPreParser::Star) {
          setState(1121);
          match(ReentPreParser::Star);
          setState(1126);
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
    setState(1129);
    match(ReentPreParser::Identifier);
    setState(1141);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Less: {
        setState(1130);
        match(ReentPreParser::Less);
        setState(1132);
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
          setState(1131);
          templateParameters();
        }
        setState(1134);
        match(ReentPreParser::Greater);
        break;
      }

      case ReentPreParser::Star:
      case ReentPreParser::And:
      case ReentPreParser::Greater:
      case ReentPreParser::AndAnd:
      case ReentPreParser::Comma:
      case ReentPreParser::Identifier: {
        setState(1138);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 160, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(1135);
            match(ReentPreParser::Identifier); 
          }
          setState(1140);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 160, _ctx);
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
    setState(1143);
    templateParameter();
    setState(1148);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(1144);
      match(ReentPreParser::Comma);
      setState(1145);
      templateParameter();
      setState(1150);
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
    setState(1153);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Identifier: {
        enterOuterAlt(_localctx, 1);
        setState(1151);
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
        setState(1152);
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
    setState(1155);
    typeItem();
    setState(1156);
    match(ReentPreParser::Identifier);
    setState(1160);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::LeftBracket) {
      setState(1157);
      dimension();
      setState(1162);
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
    setState(1163);
    match(ReentPreParser::LeftBracket);
    setState(1164);
    _la = _input->LA(1);
    if (!(_la == ReentPreParser::IntegerLiteral || _la == ReentPreParser::Identifier)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(1165);
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
    setState(1167);
    match(ReentPreParser::Goal);
    setState(1168);
    match(ReentPreParser::Is);
    setState(1169);
    prolog_predicates();
    setState(1170);
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
    setState(1172);
    match(ReentPreParser::Identifier);
    setState(1174);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftParen) {
      setState(1173);
      prolog_parameters();
    }
    setState(1178);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Is) {
      setState(1176);
      match(ReentPreParser::Is);
      setState(1177);
      prolog_predicates();
    }
    setState(1180);
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
    setState(1182);
    match(ReentPreParser::LeftParen);
    setState(1183);
    prolog_parameter();
    setState(1188);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(1184);
      match(ReentPreParser::Comma);
      setState(1185);
      prolog_parameter();
      setState(1190);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1191);
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
    setState(1196);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(1193);
      match(ReentPreParser::Newline);
      setState(1198);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1200);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Prolog_not) {
      setState(1199);
      match(ReentPreParser::Prolog_not);
    }
    setState(1202);
    prolog_predicate();
    setState(1204);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Arrow) {
      setState(1203);
      prolog_if_then();
    }
    setState(1208);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Comma

    || _la == ReentPreParser::Semi) {
      setState(1206);
      _la = _input->LA(1);
      if (!(_la == ReentPreParser::Comma

      || _la == ReentPreParser::Semi)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1207);
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
    setState(1215);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 172, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1210);
      literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1211);
      match(ReentPreParser::EmptyAtom);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1212);
      prolog_parameter_list();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(1213);
      prolog_predicate();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(1214);
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
    setState(1217);
    match(ReentPreParser::LeftBracket);
    setState(1223);
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
      | (1ULL << ReentPreParser::LeftBracket))) != 0) || ((((_la - 66) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 66)) & ((1ULL << (ReentPreParser::Prolog_not_equal - 66))
      | (1ULL << (ReentPreParser::ConstructAtom - 66))
      | (1ULL << (ReentPreParser::Underscore - 66))
      | (1ULL << (ReentPreParser::Plus - 66))
      | (1ULL << (ReentPreParser::Minus - 66))
      | (1ULL << (ReentPreParser::Not - 66))
      | (1ULL << (ReentPreParser::Assign - 66))
      | (1ULL << (ReentPreParser::Less - 66))
      | (1ULL << (ReentPreParser::Greater - 66))
      | (1ULL << (ReentPreParser::Equal - 66))
      | (1ULL << (ReentPreParser::NotEqual - 66))
      | (1ULL << (ReentPreParser::LessEqual - 66))
      | (1ULL << (ReentPreParser::GreaterEqual - 66))
      | (1ULL << (ReentPreParser::Arrow - 66))
      | (1ULL << (ReentPreParser::Semi - 66))
      | (1ULL << (ReentPreParser::Identifier - 66)))) != 0)) {
      setState(1218);
      prolog_inside_list();
      setState(1221);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Or) {
        setState(1219);
        match(ReentPreParser::Or);
        setState(1220);
        prolog_parameter();
      }
    }
    setState(1225);
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
    setState(1227);
    prolog_parameter();
    setState(1230);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Comma) {
      setState(1228);
      match(ReentPreParser::Comma);
      setState(1229);
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
    setState(1256);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 179, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1232);
      match(ReentPreParser::LeftParen);
      setState(1236);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 176, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(1233);
          match(ReentPreParser::Newline); 
        }
        setState(1238);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 176, _ctx);
      }
      setState(1239);
      prolog_predicates();
      setState(1243);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Newline) {
        setState(1240);
        match(ReentPreParser::Newline);
        setState(1245);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(1246);
      match(ReentPreParser::RightParen);
      setState(1250);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 178, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(1247);
          match(ReentPreParser::Newline); 
        }
        setState(1252);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 178, _ctx);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1253);
      match(ReentPreParser::Not);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1254);
      prolog_call();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(1255);
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
    setState(1258);
    match(ReentPreParser::Arrow);
    setState(1262);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(1259);
      match(ReentPreParser::Newline);
      setState(1264);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1266);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Prolog_not) {
      setState(1265);
      match(ReentPreParser::Prolog_not);
    }
    setState(1268);
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
    setState(1270);
    relational_expression();
    setState(1273);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Is_) {
      setState(1271);
      match(ReentPreParser::Is_);
      setState(1272);
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
    setState(1275);
    pow_expression();
    setState(1279);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (ReentPreParser::Less - 82))
      | (1ULL << (ReentPreParser::Greater - 82))
      | (1ULL << (ReentPreParser::Equal - 82))
      | (1ULL << (ReentPreParser::NotEqual - 82))
      | (1ULL << (ReentPreParser::LessEqual - 82))
      | (1ULL << (ReentPreParser::GreaterEqual - 82)))) != 0)) {
      setState(1276);
      prolog_relation();
      setState(1277);
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
    setState(1281);
    _la = _input->LA(1);
    if (!(((((_la - 82) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 82)) & ((1ULL << (ReentPreParser::Less - 82))
      | (1ULL << (ReentPreParser::Greater - 82))
      | (1ULL << (ReentPreParser::Equal - 82))
      | (1ULL << (ReentPreParser::NotEqual - 82))
      | (1ULL << (ReentPreParser::LessEqual - 82))
      | (1ULL << (ReentPreParser::GreaterEqual - 82)))) != 0))) {
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
    setState(1283);
    mul_div_expression();
    setState(1287);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Star

    || _la == ReentPreParser::Caret) {
      setState(1284);
      prolog_pow();
      setState(1285);
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
    setState(1292);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Star: {
        enterOuterAlt(_localctx, 1);
        setState(1289);
        match(ReentPreParser::Star);
        setState(1290);
        match(ReentPreParser::Star);
        break;
      }

      case ReentPreParser::Caret: {
        enterOuterAlt(_localctx, 2);
        setState(1291);
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
    setState(1294);
    plus_min_expression();
    setState(1298);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 186, _ctx)) {
    case 1: {
      setState(1295);
      prolog_mul_div();
      setState(1296);
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
    setState(1308);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::Star: {
        enterOuterAlt(_localctx, 1);
        setState(1300);
        match(ReentPreParser::Star);
        break;
      }

      case ReentPreParser::Rem: {
        enterOuterAlt(_localctx, 2);
        setState(1301);
        match(ReentPreParser::Rem);
        break;
      }

      case ReentPreParser::Div_: {
        enterOuterAlt(_localctx, 3);
        setState(1302);
        match(ReentPreParser::Div_);
        break;
      }

      case ReentPreParser::Mod_: {
        enterOuterAlt(_localctx, 4);
        setState(1303);
        match(ReentPreParser::Mod_);
        break;
      }

      case ReentPreParser::Div: {
        enterOuterAlt(_localctx, 5);
        setState(1304);
        match(ReentPreParser::Div);
        setState(1306);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::Div) {
          setState(1305);
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
    setState(1310);
    unary_expression();
    setState(1316);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 189, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1311);
        prolog_plus_minus();
        setState(1312);
        plus_min_expression(); 
      }
      setState(1318);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 189, _ctx);
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
    setState(1319);
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
    setState(1322);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::Plus

    || _la == ReentPreParser::Minus) {
      setState(1321);
      prolog_plus_minus();
    }
    setState(1324);
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
    setState(1334);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ReentPreParser::LeftParen: {
        enterOuterAlt(_localctx, 1);
        setState(1326);
        match(ReentPreParser::LeftParen);
        setState(1327);
        relational_expression();
        setState(1328);
        match(ReentPreParser::RightParen);
        break;
      }

      case ReentPreParser::LeftBracket: {
        enterOuterAlt(_localctx, 2);
        setState(1330);
        operandList();
        break;
      }

      case ReentPreParser::Identifier: {
        enterOuterAlt(_localctx, 3);
        setState(1331);
        prolog_term();
        break;
      }

      case ReentPreParser::EmptyAtom: {
        enterOuterAlt(_localctx, 4);
        setState(1332);
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
        setState(1333);
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
    setState(1336);
    match(ReentPreParser::LeftBracket);
    setState(1349);
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
      | (1ULL << ReentPreParser::LeftBracket))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 71)) & ((1ULL << (ReentPreParser::Plus - 71))
      | (1ULL << (ReentPreParser::Minus - 71))
      | (1ULL << (ReentPreParser::Identifier - 71)))) != 0)) {
      setState(1337);
      relational_expression();
      setState(1342);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Comma) {
        setState(1338);
        match(ReentPreParser::Comma);
        setState(1339);
        relational_expression();
        setState(1344);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(1347);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ReentPreParser::Or) {
        setState(1345);
        match(ReentPreParser::Or);
        setState(1346);
        relational_expression();
      }
    }
    setState(1351);
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
    setState(1353);
    match(ReentPreParser::Identifier);
    setState(1366);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ReentPreParser::LeftParen) {
      setState(1354);
      match(ReentPreParser::LeftParen);
      setState(1363);
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
        | (1ULL << ReentPreParser::LeftBracket))) != 0) || ((((_la - 71) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 71)) & ((1ULL << (ReentPreParser::Plus - 71))
        | (1ULL << (ReentPreParser::Minus - 71))
        | (1ULL << (ReentPreParser::Identifier - 71)))) != 0)) {
        setState(1355);
        relational_expression();
        setState(1360);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == ReentPreParser::Comma) {
          setState(1356);
          match(ReentPreParser::Comma);
          setState(1357);
          relational_expression();
          setState(1362);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(1365);
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
    setState(1375);
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
        setState(1368);
        prolog_predicate_id();
        setState(1369);
        prolog_call_params();
        break;
      }

      case ReentPreParser::Identifier: {
        enterOuterAlt(_localctx, 2);
        setState(1371);
        match(ReentPreParser::Identifier);
        setState(1373);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ReentPreParser::LeftParen) {
          setState(1372);
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
    setState(1377);
    match(ReentPreParser::LeftParen);
    setState(1381);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(1378);
      match(ReentPreParser::Newline);
      setState(1383);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1384);
    prolog_parameter();
    setState(1395);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Comma) {
      setState(1385);
      match(ReentPreParser::Comma);
      setState(1389);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ReentPreParser::Newline) {
        setState(1386);
        match(ReentPreParser::Newline);
        setState(1391);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(1392);
      prolog_parameter();
      setState(1397);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1401);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ReentPreParser::Newline) {
      setState(1398);
      match(ReentPreParser::Newline);
      setState(1403);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1404);
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
    setState(1406);
    _la = _input->LA(1);
    if (!(((((_la - 66) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 66)) & ((1ULL << (ReentPreParser::Prolog_not_equal - 66))
      | (1ULL << (ReentPreParser::ConstructAtom - 66))
      | (1ULL << (ReentPreParser::Assign - 66))
      | (1ULL << (ReentPreParser::Less - 66))
      | (1ULL << (ReentPreParser::Greater - 66))
      | (1ULL << (ReentPreParser::Equal - 66))
      | (1ULL << (ReentPreParser::NotEqual - 66))
      | (1ULL << (ReentPreParser::LessEqual - 66))
      | (1ULL << (ReentPreParser::GreaterEqual - 66))
      | (1ULL << (ReentPreParser::Arrow - 66))
      | (1ULL << (ReentPreParser::Semi - 66)))) != 0))) {
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
    setState(1409); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(1408);
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
      setState(1411); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 204, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
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
  enterRule(_localctx, 190, ReentPreParser::RuleOtherLine);
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
    setState(1413);

    if (!( _input->LT(-1) == NULL || _input->LT(-1)->getText() == "\n" )) throw FailedPredicateException(this, " _input->LT(-1) == NULL || _input->LT(-1)->getText() == \"\\n\" ");
    setState(1417);
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
      | (1ULL << ReentPreParser::Or_)
      | (1ULL << ReentPreParser::At)
      | (1ULL << ReentPreParser::Is))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (ReentPreParser::Is_ - 64))
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
      setState(1414);
      _la = _input->LA(1);
      if (_la == 0 || _la == Token::EOF || (_la == ReentPreParser::Newline)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(1419);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1420);
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
  enterRule(_localctx, 192, ReentPreParser::RuleLiteral);
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
    setState(1422);
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
    case 95: return otherLineSempred(dynamic_cast<OtherLineContext *>(context), predicateIndex);

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
  "prolog_predicate_id", "cpp_code_without_at", "otherLine", "literal"
};

std::vector<std::string> ReentPreParser::_literalNames = {
  "", "", "", "", "", "", "", "''''", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "'@Value'", "'conditions'", 
  "'controlled'", "'div'", "'false'", "'feed_forward'", "'text()'", "'goal'", 
  "'lin_extrapolator'", "'mgua'", "'mod'", "'nullptr'", "'analyze'", "'@begin'", 
  "'@end'", "'parallel'", "'sequential'", "'rem'", "'true'", "')->{'", "')==>{'", 
  "')!=>{'", "')\u003F=>{'", "'('", "')'", "'['", "']'", "'{'", "'}'", "'=>'", 
  "'//'", "'#'", "'and'", "'or'", "'@'", "':-'", "'is'", "'\\+'", "'\\='", 
  "'\\'", "'=..'", "'$'", "'_'", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", 
  "'&'", "'|'", "'~'", "", "'='", "'<'", "'>'", "'=='", "'!='", "'<='", 
  "'>='", "", "", "','", "'->'", "'\u003F'", "':'", "'::'", "';'", "'.'", 
  "'.*'", "'...'"
};

std::vector<std::string> ReentPreParser::_symbolicNames = {
  "", "Regexp_fragment", "Regexp_set", "IntegerLiteral", "CharacterLiteral", 
  "FloatingLiteral", "StringLiteral", "EmptyAtom", "BooleanLiteral", "PointerLiteral", 
  "UserDefinedLiteral", "DefModule", "DefMemoization", "DoNotCheck", "DefOtherPragma", 
  "Introduce", "MetaSentence", "Stop", "PreprocPasses", "AddScan", "Scan", 
  "AddParse", "Parse", "DefPattern", "DefXPath", "Line", "MultiLineMacro", 
  "Directive", "AtValue", "Conditions", "Controlled", "Div_", "False_", 
  "Feed_forward", "GetText", "Goal", "Lin_extrapolator", "Mgua", "Mod_", 
  "Nullptr", "Regexp_analyze", "Regexp_begin", "Regexp_end", "Regexp_parallel", 
  "Regexp_sequential", "Rem", "True_", "Plc_regexp_var", "Plc_regexp_equal", 
  "Plc_regexp_not_equal", "Plc_regexp_query", "LeftParen", "RightParen", 
  "LeftBracket", "RightBracket", "LeftBrace", "RightBrace", "AssignGreater", 
  "DivDiv", "Pound", "And_", "Or_", "At", "Is", "Is_", "Prolog_not", "Prolog_not_equal", 
  "Slash", "ConstructAtom", "Regexp_ref", "Underscore", "Plus", "Minus", 
  "Star", "Div", "Mod", "Caret", "And", "Or", "Tilde", "Not", "Assign", 
  "Less", "Greater", "Equal", "NotEqual", "LessEqual", "GreaterEqual", "AndAnd", 
  "OrOr", "Comma", "Arrow", "Question", "Colon", "Doublecolon", "Semi", 
  "Dot", "DotStar", "Ellipsis", "Identifier", "DecimalLiteral", "OctalLiteral", 
  "HexadecimalLiteral", "BinaryLiteral", "Integersuffix", "UserDefinedIntegerLiteral", 
  "UserDefinedFloatingLiteral", "UserDefinedStringLiteral", "UserDefinedCharacterLiteral", 
  "Whitespace", "Newline", "BlockComment", "LineComment", "PrologComment"
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
       0x3, 0x73, 0x593, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
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
       0x9, 0x62, 0x3, 0x2, 0x5, 0x2, 0xc6, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 
       0x3, 0x2, 0x3, 0x3, 0x6, 0x3, 0xcc, 0xa, 0x3, 0xd, 0x3, 0xe, 0x3, 
       0xcd, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
       0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
       0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0xec, 0xa, 0x4, 0x3, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x5, 0x5, 0xf6, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
       0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x100, 0xa, 0x5, 
       0xc, 0x5, 0xe, 0x5, 0x103, 0xb, 0x5, 0x5, 0x5, 0x105, 0xa, 0x5, 0x3, 
       0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 
       0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
       0x7, 0x3, 0x7, 0x7, 0x7, 0x116, 0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x119, 
       0xb, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x11d, 0xa, 0x7, 0x5, 0x7, 
       0x11f, 0xa, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 
       0x125, 0xa, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 0x8, 0x12a, 0xa, 
       0x8, 0xc, 0x8, 0xe, 0x8, 0x12d, 0xb, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 
       0x9, 0x7, 0x9, 0x132, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x135, 0xb, 0x9, 
       0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x13a, 0xa, 0xa, 0xc, 0xa, 
       0xe, 0xa, 0x13d, 0xb, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 
       0x142, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x145, 0xb, 0xb, 0x3, 0xc, 0x3, 
       0xc, 0x3, 0xc, 0x7, 0xc, 0x14a, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x14d, 
       0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
       0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
       0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x15e, 0xa, 0xd, 0x3, 0xd, 
       0x5, 0xd, 0x161, 0xa, 0xd, 0x5, 0xd, 0x163, 0xa, 0xd, 0x3, 0xe, 0x5, 
       0xe, 0x166, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x16b, 
       0xa, 0xe, 0x3, 0xe, 0x5, 0xe, 0x16e, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 
       0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x174, 0xa, 0xe, 0x3, 0xe, 0x5, 0xe, 
       0x177, 0xa, 0xe, 0x7, 0xe, 0x179, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0x17c, 
       0xb, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x182, 
       0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x186, 0xa, 0xe, 0x3, 0xf, 
       0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x7, 
       0x10, 0x18f, 0xa, 0x10, 0xc, 0x10, 0xe, 0x10, 0x192, 0xb, 0x10, 0x3, 
       0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
       0x11, 0x7, 0x11, 0x19b, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 0x19e, 0xb, 
       0x11, 0x5, 0x11, 0x1a0, 0xa, 0x11, 0x3, 0x11, 0x5, 0x11, 0x1a3, 0xa, 
       0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
       0x11, 0x3, 0x12, 0x5, 0x12, 0x1ac, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 
       0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x1b3, 0xa, 0x13, 0x3, 
       0x13, 0x3, 0x13, 0x5, 0x13, 0x1b7, 0xa, 0x13, 0x3, 0x13, 0x7, 0x13, 
       0x1ba, 0xa, 0x13, 0xc, 0x13, 0xe, 0x13, 0x1bd, 0xb, 0x13, 0x3, 0x13, 
       0x5, 0x13, 0x1c0, 0xa, 0x13, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x1c4, 
       0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x1c8, 0xa, 0x14, 0x3, 
       0x14, 0x7, 0x14, 0x1cb, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0x1ce, 0xb, 
       0x14, 0x3, 0x14, 0x5, 0x14, 0x1d1, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 
       0x5, 0x15, 0x1d5, 0xa, 0x15, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0x1d9, 
       0xa, 0x15, 0x3, 0x15, 0x7, 0x15, 0x1dc, 0xa, 0x15, 0xc, 0x15, 0xe, 
       0x15, 0x1df, 0xb, 0x15, 0x3, 0x15, 0x5, 0x15, 0x1e2, 0xa, 0x15, 0x3, 
       0x16, 0x3, 0x16, 0x5, 0x16, 0x1e6, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 
       0x5, 0x16, 0x1ea, 0xa, 0x16, 0x3, 0x16, 0x7, 0x16, 0x1ed, 0xa, 0x16, 
       0xc, 0x16, 0xe, 0x16, 0x1f0, 0xb, 0x16, 0x3, 0x16, 0x5, 0x16, 0x1f3, 
       0xa, 0x16, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x1f7, 0xa, 0x17, 0x3, 
       0x17, 0x3, 0x17, 0x5, 0x17, 0x1fb, 0xa, 0x17, 0x3, 0x17, 0x7, 0x17, 
       0x1fe, 0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 0x201, 0xb, 0x17, 0x3, 0x17, 
       0x5, 0x17, 0x204, 0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
       0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
       0x18, 0x3, 0x18, 0x5, 0x18, 0x211, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 
       0x5, 0x18, 0x215, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x219, 
       0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x21d, 0xa, 0x18, 0x3, 
       0x18, 0x3, 0x18, 0x5, 0x18, 0x221, 0xa, 0x18, 0x3, 0x18, 0x5, 0x18, 
       0x224, 0xa, 0x18, 0x3, 0x18, 0x5, 0x18, 0x227, 0xa, 0x18, 0x3, 0x18, 
       0x3, 0x18, 0x5, 0x18, 0x22b, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 
       0x18, 0x22f, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x233, 0xa, 
       0x18, 0x3, 0x19, 0x5, 0x19, 0x236, 0xa, 0x19, 0x3, 0x19, 0x5, 0x19, 
       0x239, 0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x23d, 0xa, 0x19, 
       0x3, 0x19, 0x5, 0x19, 0x240, 0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 
       0x19, 0x244, 0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x248, 0xa, 
       0x19, 0x3, 0x19, 0x5, 0x19, 0x24b, 0xa, 0x19, 0x7, 0x19, 0x24d, 0xa, 
       0x19, 0xc, 0x19, 0xe, 0x19, 0x250, 0xb, 0x19, 0x3, 0x19, 0x3, 0x19, 
       0x5, 0x19, 0x254, 0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
       0x19, 0x3, 0x19, 0x5, 0x19, 0x25b, 0xa, 0x19, 0x5, 0x19, 0x25d, 0xa, 
       0x19, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x261, 0xa, 0x1a, 0x3, 0x1a, 
       0x3, 0x1a, 0x5, 0x1a, 0x265, 0xa, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 
       0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x26b, 0xa, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 
       0x5, 0x1b, 0x26f, 0xa, 0x1b, 0x3, 0x1b, 0x7, 0x1b, 0x272, 0xa, 0x1b, 
       0xc, 0x1b, 0xe, 0x1b, 0x275, 0xb, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x278, 
       0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 0x27d, 0xa, 
       0x1c, 0xc, 0x1c, 0xe, 0x1c, 0x280, 0xb, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
       0x3, 0x1c, 0x7, 0x1c, 0x285, 0xa, 0x1c, 0xc, 0x1c, 0xe, 0x1c, 0x288, 
       0xb, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x28c, 0xa, 0x1c, 0x3, 
       0x1c, 0x7, 0x1c, 0x28f, 0xa, 0x1c, 0xc, 0x1c, 0xe, 0x1c, 0x292, 0xb, 
       0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 0x5, 
       0x1d, 0x299, 0xa, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 
       0x3, 0x1e, 0x3, 0x1e, 0x7, 0x1e, 0x2a1, 0xa, 0x1e, 0xc, 0x1e, 0xe, 
       0x1e, 0x2a4, 0xb, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x2a8, 0xa, 
       0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x2ac, 0xa, 0x1e, 0x3, 0x1e, 
       0x5, 0x1e, 0x2af, 0xa, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
       0x1f, 0x5, 0x1f, 0x2b5, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
       0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
       0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x2c3, 0xa, 0x20, 0x3, 
       0x21, 0x3, 0x21, 0x3, 0x21, 0x5, 0x21, 0x2c8, 0xa, 0x21, 0x3, 0x21, 
       0x3, 0x21, 0x3, 0x21, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 
       0x2d0, 0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 
       0x23, 0x3, 0x23, 0x5, 0x23, 0x2d8, 0xa, 0x23, 0x3, 0x23, 0x3, 0x23, 
       0x3, 0x24, 0x5, 0x24, 0x2dd, 0xa, 0x24, 0x3, 0x24, 0x3, 0x24, 0x5, 
       0x24, 0x2e1, 0xa, 0x24, 0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x2e5, 0xa, 
       0x24, 0x3, 0x24, 0x7, 0x24, 0x2e8, 0xa, 0x24, 0xc, 0x24, 0xe, 0x24, 
       0x2eb, 0xb, 0x24, 0x3, 0x24, 0x5, 0x24, 0x2ee, 0xa, 0x24, 0x3, 0x25, 
       0x5, 0x25, 0x2f1, 0xa, 0x25, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 0x2f5, 
       0xa, 0x25, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 0x2f9, 0xa, 0x25, 0x3, 
       0x25, 0x7, 0x25, 0x2fc, 0xa, 0x25, 0xc, 0x25, 0xe, 0x25, 0x2ff, 0xb, 
       0x25, 0x3, 0x25, 0x5, 0x25, 0x302, 0xa, 0x25, 0x3, 0x26, 0x5, 0x26, 
       0x305, 0xa, 0x26, 0x3, 0x26, 0x3, 0x26, 0x5, 0x26, 0x309, 0xa, 0x26, 
       0x3, 0x26, 0x3, 0x26, 0x5, 0x26, 0x30d, 0xa, 0x26, 0x3, 0x26, 0x3, 
       0x26, 0x5, 0x26, 0x311, 0xa, 0x26, 0x3, 0x26, 0x5, 0x26, 0x314, 0xa, 
       0x26, 0x3, 0x26, 0x3, 0x26, 0x5, 0x26, 0x318, 0xa, 0x26, 0x5, 0x26, 
       0x31a, 0xa, 0x26, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x31f, 
       0xa, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x324, 0xa, 
       0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x328, 0xa, 0x27, 0x3, 0x27, 
       0x3, 0x27, 0x5, 0x27, 0x32c, 0xa, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 
       0x27, 0x330, 0xa, 0x27, 0x3, 0x27, 0x7, 0x27, 0x333, 0xa, 0x27, 0xc, 
       0x27, 0xe, 0x27, 0x336, 0xb, 0x27, 0x5, 0x27, 0x338, 0xa, 0x27, 0x3, 
       0x27, 0x5, 0x27, 0x33b, 0xa, 0x27, 0x3, 0x27, 0x5, 0x27, 0x33e, 0xa, 
       0x27, 0x5, 0x27, 0x340, 0xa, 0x27, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 
       0x3, 0x28, 0x5, 0x28, 0x346, 0xa, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 
       0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 0x34f, 
       0xa, 0x28, 0x3, 0x29, 0x3, 0x29, 0x5, 0x29, 0x353, 0xa, 0x29, 0x3, 
       0x29, 0x3, 0x29, 0x5, 0x29, 0x357, 0xa, 0x29, 0x3, 0x29, 0x3, 0x29, 
       0x5, 0x29, 0x35b, 0xa, 0x29, 0x3, 0x29, 0x5, 0x29, 0x35e, 0xa, 0x29, 
       0x3, 0x29, 0x5, 0x29, 0x361, 0xa, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 
       0x2a, 0x5, 0x2a, 0x366, 0xa, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 
       0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 
       0x7, 0x2a, 0x371, 0xa, 0x2a, 0xc, 0x2a, 0xe, 0x2a, 0x374, 0xb, 0x2a, 
       0x5, 0x2a, 0x376, 0xa, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x7, 
       0x2a, 0x37b, 0xa, 0x2a, 0xc, 0x2a, 0xe, 0x2a, 0x37e, 0xb, 0x2a, 0x3, 
       0x2a, 0x3, 0x2a, 0x7, 0x2a, 0x382, 0xa, 0x2a, 0xc, 0x2a, 0xe, 0x2a, 
       0x385, 0xb, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x7, 0x2a, 0x389, 0xa, 0x2a, 
       0xc, 0x2a, 0xe, 0x2a, 0x38c, 0xb, 0x2a, 0x3, 0x2b, 0x3, 0x2b, 0x3, 
       0x2b, 0x3, 0x2b, 0x5, 0x2b, 0x392, 0xa, 0x2b, 0x3, 0x2c, 0x3, 0x2c, 
       0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x398, 0xa, 0x2c, 0x3, 0x2c, 0x5, 
       0x2c, 0x39b, 0xa, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 
       0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x7, 0x2d, 
       0x3a6, 0xa, 0x2d, 0xc, 0x2d, 0xe, 0x2d, 0x3a9, 0xb, 0x2d, 0x3, 0x2d, 
       0x3, 0x2d, 0x5, 0x2d, 0x3ad, 0xa, 0x2d, 0x3, 0x2d, 0x6, 0x2d, 0x3b0, 
       0xa, 0x2d, 0xd, 0x2d, 0xe, 0x2d, 0x3b1, 0x3, 0x2d, 0x3, 0x2d, 0x3, 
       0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x5, 0x2e, 0x3bb, 
       0xa, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 
       0x3, 0x2f, 0x3, 0x2f, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 0x3, 0x30, 
       0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x32, 0x3, 0x32, 
       0x3, 0x32, 0x3, 0x32, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 
       0x3, 0x33, 0x3, 0x33, 0x7, 0x33, 0x3d6, 0xa, 0x33, 0xc, 0x33, 0xe, 
       0x33, 0x3d9, 0xb, 0x33, 0x3, 0x33, 0x3, 0x33, 0x3, 0x34, 0x5, 0x34, 
       0x3de, 0xa, 0x34, 0x3, 0x34, 0x3, 0x34, 0x3, 0x35, 0x3, 0x35, 0x3, 
       0x35, 0x5, 0x35, 0x3e5, 0xa, 0x35, 0x3, 0x36, 0x6, 0x36, 0x3e8, 0xa, 
       0x36, 0xd, 0x36, 0xe, 0x36, 0x3e9, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 
       0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 
       0x3f4, 0xa, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x37, 0x3, 0x37, 0x3, 
       0x37, 0x5, 0x37, 0x3fb, 0xa, 0x37, 0x3, 0x37, 0x5, 0x37, 0x3fe, 0xa, 
       0x37, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 
       0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
       0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x5, 0x39, 0x410, 
       0xa, 0x39, 0x5, 0x39, 0x412, 0xa, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 
       0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 
       0x3a, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3b, 0x3, 0x3c, 0x3, 
       0x3c, 0x3, 0x3c, 0x5, 0x3c, 0x424, 0xa, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 
       0x5, 0x3d, 0x428, 0xa, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 
       0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3f, 0x3, 0x3f, 0x3, 
       0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x40, 0x6, 
       0x40, 0x439, 0xa, 0x40, 0xd, 0x40, 0xe, 0x40, 0x43a, 0x3, 0x40, 0x3, 
       0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 
       0x40, 0x3, 0x40, 0x7, 0x40, 0x446, 0xa, 0x40, 0xc, 0x40, 0xe, 0x40, 
       0x449, 0xb, 0x40, 0x5, 0x40, 0x44b, 0xa, 0x40, 0x3, 0x40, 0x3, 0x40, 
       0x3, 0x40, 0x7, 0x40, 0x450, 0xa, 0x40, 0xc, 0x40, 0xe, 0x40, 0x453, 
       0xb, 0x40, 0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x457, 0xa, 0x40, 0xc, 
       0x40, 0xe, 0x40, 0x45a, 0xb, 0x40, 0x3, 0x40, 0x6, 0x40, 0x45d, 0xa, 
       0x40, 0xd, 0x40, 0xe, 0x40, 0x45e, 0x3, 0x41, 0x3, 0x41, 0x3, 0x41, 
       0x3, 0x41, 0x7, 0x41, 0x465, 0xa, 0x41, 0xc, 0x41, 0xe, 0x41, 0x468, 
       0xb, 0x41, 0x5, 0x41, 0x46a, 0xa, 0x41, 0x3, 0x42, 0x3, 0x42, 0x3, 
       0x42, 0x5, 0x42, 0x46f, 0xa, 0x42, 0x3, 0x42, 0x3, 0x42, 0x7, 0x42, 
       0x473, 0xa, 0x42, 0xc, 0x42, 0xe, 0x42, 0x476, 0xb, 0x42, 0x5, 0x42, 
       0x478, 0xa, 0x42, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x7, 0x43, 0x47d, 
       0xa, 0x43, 0xc, 0x43, 0xe, 0x43, 0x480, 0xb, 0x43, 0x3, 0x44, 0x3, 
       0x44, 0x5, 0x44, 0x484, 0xa, 0x44, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 
       0x7, 0x45, 0x489, 0xa, 0x45, 0xc, 0x45, 0xe, 0x45, 0x48c, 0xb, 0x45, 
       0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x3, 0x47, 0x3, 0x47, 
       0x3, 0x47, 0x3, 0x47, 0x3, 0x47, 0x3, 0x48, 0x3, 0x48, 0x5, 0x48, 
       0x499, 0xa, 0x48, 0x3, 0x48, 0x3, 0x48, 0x5, 0x48, 0x49d, 0xa, 0x48, 
       0x3, 0x48, 0x3, 0x48, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 
       0x7, 0x49, 0x4a5, 0xa, 0x49, 0xc, 0x49, 0xe, 0x49, 0x4a8, 0xb, 0x49, 
       0x3, 0x49, 0x3, 0x49, 0x3, 0x4a, 0x7, 0x4a, 0x4ad, 0xa, 0x4a, 0xc, 
       0x4a, 0xe, 0x4a, 0x4b0, 0xb, 0x4a, 0x3, 0x4a, 0x5, 0x4a, 0x4b3, 0xa, 
       0x4a, 0x3, 0x4a, 0x3, 0x4a, 0x5, 0x4a, 0x4b7, 0xa, 0x4a, 0x3, 0x4a, 
       0x3, 0x4a, 0x5, 0x4a, 0x4bb, 0xa, 0x4a, 0x3, 0x4b, 0x3, 0x4b, 0x3, 
       0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x5, 0x4b, 0x4c2, 0xa, 0x4b, 0x3, 0x4c, 
       0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x4c8, 0xa, 0x4c, 0x5, 
       0x4c, 0x4ca, 0xa, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4d, 0x3, 0x4d, 
       0x3, 0x4d, 0x5, 0x4d, 0x4d1, 0xa, 0x4d, 0x3, 0x4e, 0x3, 0x4e, 0x7, 
       0x4e, 0x4d5, 0xa, 0x4e, 0xc, 0x4e, 0xe, 0x4e, 0x4d8, 0xb, 0x4e, 0x3, 
       0x4e, 0x3, 0x4e, 0x7, 0x4e, 0x4dc, 0xa, 0x4e, 0xc, 0x4e, 0xe, 0x4e, 
       0x4df, 0xb, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x7, 0x4e, 0x4e3, 0xa, 0x4e, 
       0xc, 0x4e, 0xe, 0x4e, 0x4e6, 0xb, 0x4e, 0x3, 0x4e, 0x3, 0x4e, 0x3, 
       0x4e, 0x5, 0x4e, 0x4eb, 0xa, 0x4e, 0x3, 0x4f, 0x3, 0x4f, 0x7, 0x4f, 
       0x4ef, 0xa, 0x4f, 0xc, 0x4f, 0xe, 0x4f, 0x4f2, 0xb, 0x4f, 0x3, 0x4f, 
       0x5, 0x4f, 0x4f5, 0xa, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x50, 0x3, 
       0x50, 0x3, 0x50, 0x5, 0x50, 0x4fc, 0xa, 0x50, 0x3, 0x51, 0x3, 0x51, 
       0x3, 0x51, 0x3, 0x51, 0x5, 0x51, 0x502, 0xa, 0x51, 0x3, 0x52, 0x3, 
       0x52, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x5, 0x53, 0x50a, 
       0xa, 0x53, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x5, 0x54, 0x50f, 0xa, 
       0x54, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x5, 0x55, 0x515, 
       0xa, 0x55, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 
       0x3, 0x56, 0x5, 0x56, 0x51d, 0xa, 0x56, 0x5, 0x56, 0x51f, 0xa, 0x56, 
       0x3, 0x57, 0x3, 0x57, 0x3, 0x57, 0x3, 0x57, 0x7, 0x57, 0x525, 0xa, 
       0x57, 0xc, 0x57, 0xe, 0x57, 0x528, 0xb, 0x57, 0x3, 0x58, 0x3, 0x58, 
       0x3, 0x59, 0x5, 0x59, 0x52d, 0xa, 0x59, 0x3, 0x59, 0x3, 0x59, 0x3, 
       0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5a, 0x3, 
       0x5a, 0x3, 0x5a, 0x5, 0x5a, 0x539, 0xa, 0x5a, 0x3, 0x5b, 0x3, 0x5b, 
       0x3, 0x5b, 0x3, 0x5b, 0x7, 0x5b, 0x53f, 0xa, 0x5b, 0xc, 0x5b, 0xe, 
       0x5b, 0x542, 0xb, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 0x5, 0x5b, 0x546, 0xa, 
       0x5b, 0x5, 0x5b, 0x548, 0xa, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5c, 
       0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x3, 0x5c, 0x7, 0x5c, 0x551, 0xa, 
       0x5c, 0xc, 0x5c, 0xe, 0x5c, 0x554, 0xb, 0x5c, 0x5, 0x5c, 0x556, 0xa, 
       0x5c, 0x3, 0x5c, 0x5, 0x5c, 0x559, 0xa, 0x5c, 0x3, 0x5d, 0x3, 0x5d, 
       0x3, 0x5d, 0x3, 0x5d, 0x3, 0x5d, 0x5, 0x5d, 0x560, 0xa, 0x5d, 0x5, 
       0x5d, 0x562, 0xa, 0x5d, 0x3, 0x5e, 0x3, 0x5e, 0x7, 0x5e, 0x566, 0xa, 
       0x5e, 0xc, 0x5e, 0xe, 0x5e, 0x569, 0xb, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 
       0x3, 0x5e, 0x7, 0x5e, 0x56e, 0xa, 0x5e, 0xc, 0x5e, 0xe, 0x5e, 0x571, 
       0xb, 0x5e, 0x3, 0x5e, 0x7, 0x5e, 0x574, 0xa, 0x5e, 0xc, 0x5e, 0xe, 
       0x5e, 0x577, 0xb, 0x5e, 0x3, 0x5e, 0x7, 0x5e, 0x57a, 0xa, 0x5e, 0xc, 
       0x5e, 0xe, 0x5e, 0x57d, 0xb, 0x5e, 0x3, 0x5e, 0x3, 0x5e, 0x3, 0x5f, 
       0x3, 0x5f, 0x3, 0x60, 0x6, 0x60, 0x584, 0xa, 0x60, 0xd, 0x60, 0xe, 
       0x60, 0x585, 0x3, 0x61, 0x3, 0x61, 0x7, 0x61, 0x58a, 0xa, 0x61, 0xc, 
       0x61, 0xe, 0x61, 0x58d, 0xb, 0x61, 0x3, 0x61, 0x3, 0x61, 0x3, 0x62, 
       0x3, 0x62, 0x3, 0x62, 0x2, 0x2, 0x63, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 
       0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 
       0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 
       0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 
       0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 
       0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 
       0x7c, 0x7e, 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 
       0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 0xa6, 
       0xa8, 0xaa, 0xac, 0xae, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 
       0xbe, 0xc0, 0xc2, 0x2, 0x11, 0x4, 0x2, 0x53, 0x55, 0x57, 0x59, 0x3, 
       0x2, 0x4b, 0x4c, 0x3, 0x2, 0x49, 0x4a, 0x4, 0x2, 0x3c, 0x3c, 0x4c, 
       0x4c, 0x4, 0x2, 0x4b, 0x4b, 0x65, 0x65, 0x4, 0x2, 0x35, 0x38, 0x5c, 
       0x5c, 0x5, 0x2, 0x5, 0x5, 0x7, 0x7, 0x65, 0x65, 0x4, 0x2, 0x5, 0x5, 
       0x7, 0x7, 0x3, 0x2, 0x70, 0x70, 0x4, 0x2, 0x5, 0x5, 0x65, 0x65, 0x4, 
       0x2, 0x5c, 0x5c, 0x61, 0x61, 0x3, 0x2, 0x54, 0x59, 0x7, 0x2, 0x44, 
       0x44, 0x46, 0x46, 0x53, 0x59, 0x5d, 0x5d, 0x61, 0x61, 0x4, 0x2, 0x3a, 
       0x3a, 0x40, 0x40, 0x4, 0x2, 0x5, 0x8, 0xa, 0xc, 0x2, 0x642, 0x2, 
       0xc5, 0x3, 0x2, 0x2, 0x2, 0x4, 0xcb, 0x3, 0x2, 0x2, 0x2, 0x6, 0xeb, 
       0x3, 0x2, 0x2, 0x2, 0x8, 0xed, 0x3, 0x2, 0x2, 0x2, 0xa, 0x10b, 0x3, 
       0x2, 0x2, 0x2, 0xc, 0x124, 0x3, 0x2, 0x2, 0x2, 0xe, 0x126, 0x3, 0x2, 
       0x2, 0x2, 0x10, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x12, 0x136, 0x3, 0x2, 
       0x2, 0x2, 0x14, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x16, 0x146, 0x3, 0x2, 
       0x2, 0x2, 0x18, 0x162, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x165, 0x3, 0x2, 
       0x2, 0x2, 0x1c, 0x187, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x18b, 0x3, 0x2, 
       0x2, 0x2, 0x20, 0x193, 0x3, 0x2, 0x2, 0x2, 0x22, 0x1ab, 0x3, 0x2, 
       0x2, 0x2, 0x24, 0x1b0, 0x3, 0x2, 0x2, 0x2, 0x26, 0x1c1, 0x3, 0x2, 
       0x2, 0x2, 0x28, 0x1d2, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x1e3, 0x3, 0x2, 
       0x2, 0x2, 0x2c, 0x1f4, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x232, 0x3, 0x2, 
       0x2, 0x2, 0x30, 0x235, 0x3, 0x2, 0x2, 0x2, 0x32, 0x25e, 0x3, 0x2, 
       0x2, 0x2, 0x34, 0x268, 0x3, 0x2, 0x2, 0x2, 0x36, 0x279, 0x3, 0x2, 
       0x2, 0x2, 0x38, 0x298, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x29c, 0x3, 0x2, 
       0x2, 0x2, 0x3c, 0x2b4, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x2b6, 0x3, 0x2, 
       0x2, 0x2, 0x40, 0x2c4, 0x3, 0x2, 0x2, 0x2, 0x42, 0x2cc, 0x3, 0x2, 
       0x2, 0x2, 0x44, 0x2d4, 0x3, 0x2, 0x2, 0x2, 0x46, 0x2dc, 0x3, 0x2, 
       0x2, 0x2, 0x48, 0x2f0, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x319, 0x3, 0x2, 
       0x2, 0x2, 0x4c, 0x33f, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x34e, 0x3, 0x2, 
       0x2, 0x2, 0x50, 0x350, 0x3, 0x2, 0x2, 0x2, 0x52, 0x362, 0x3, 0x2, 
       0x2, 0x2, 0x54, 0x38d, 0x3, 0x2, 0x2, 0x2, 0x56, 0x39a, 0x3, 0x2, 
       0x2, 0x2, 0x58, 0x39c, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x3b5, 0x3, 0x2, 
       0x2, 0x2, 0x5c, 0x3bf, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x3c3, 0x3, 0x2, 
       0x2, 0x2, 0x60, 0x3c7, 0x3, 0x2, 0x2, 0x2, 0x62, 0x3cb, 0x3, 0x2, 
       0x2, 0x2, 0x64, 0x3cf, 0x3, 0x2, 0x2, 0x2, 0x66, 0x3dd, 0x3, 0x2, 
       0x2, 0x2, 0x68, 0x3e4, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x3f3, 0x3, 0x2, 
       0x2, 0x2, 0x6c, 0x3fa, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x3ff, 0x3, 0x2, 
       0x2, 0x2, 0x70, 0x404, 0x3, 0x2, 0x2, 0x2, 0x72, 0x415, 0x3, 0x2, 
       0x2, 0x2, 0x74, 0x41c, 0x3, 0x2, 0x2, 0x2, 0x76, 0x423, 0x3, 0x2, 
       0x2, 0x2, 0x78, 0x427, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x429, 0x3, 0x2, 
       0x2, 0x2, 0x7c, 0x430, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x438, 0x3, 0x2, 
       0x2, 0x2, 0x80, 0x460, 0x3, 0x2, 0x2, 0x2, 0x82, 0x46b, 0x3, 0x2, 
       0x2, 0x2, 0x84, 0x479, 0x3, 0x2, 0x2, 0x2, 0x86, 0x483, 0x3, 0x2, 
       0x2, 0x2, 0x88, 0x485, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x48d, 0x3, 0x2, 
       0x2, 0x2, 0x8c, 0x491, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x496, 0x3, 0x2, 
       0x2, 0x2, 0x90, 0x4a0, 0x3, 0x2, 0x2, 0x2, 0x92, 0x4ae, 0x3, 0x2, 
       0x2, 0x2, 0x94, 0x4c1, 0x3, 0x2, 0x2, 0x2, 0x96, 0x4c3, 0x3, 0x2, 
       0x2, 0x2, 0x98, 0x4cd, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x4ea, 0x3, 0x2, 
       0x2, 0x2, 0x9c, 0x4ec, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x4f8, 0x3, 0x2, 
       0x2, 0x2, 0xa0, 0x4fd, 0x3, 0x2, 0x2, 0x2, 0xa2, 0x503, 0x3, 0x2, 
       0x2, 0x2, 0xa4, 0x505, 0x3, 0x2, 0x2, 0x2, 0xa6, 0x50e, 0x3, 0x2, 
       0x2, 0x2, 0xa8, 0x510, 0x3, 0x2, 0x2, 0x2, 0xaa, 0x51e, 0x3, 0x2, 
       0x2, 0x2, 0xac, 0x520, 0x3, 0x2, 0x2, 0x2, 0xae, 0x529, 0x3, 0x2, 
       0x2, 0x2, 0xb0, 0x52c, 0x3, 0x2, 0x2, 0x2, 0xb2, 0x538, 0x3, 0x2, 
       0x2, 0x2, 0xb4, 0x53a, 0x3, 0x2, 0x2, 0x2, 0xb6, 0x54b, 0x3, 0x2, 
       0x2, 0x2, 0xb8, 0x561, 0x3, 0x2, 0x2, 0x2, 0xba, 0x563, 0x3, 0x2, 
       0x2, 0x2, 0xbc, 0x580, 0x3, 0x2, 0x2, 0x2, 0xbe, 0x583, 0x3, 0x2, 
       0x2, 0x2, 0xc0, 0x587, 0x3, 0x2, 0x2, 0x2, 0xc2, 0x590, 0x3, 0x2, 
       0x2, 0x2, 0xc4, 0xc6, 0x5, 0x4, 0x3, 0x2, 0xc5, 0xc4, 0x3, 0x2, 0x2, 
       0x2, 0xc5, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc7, 0x3, 0x2, 0x2, 0x2, 
       0xc7, 0xc8, 0x7, 0x2, 0x2, 0x3, 0xc8, 0xc9, 0x8, 0x2, 0x1, 0x2, 0xc9, 
       0x3, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcc, 0x5, 0x6, 0x4, 0x2, 0xcb, 0xca, 
       0x3, 0x2, 0x2, 0x2, 0xcc, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xcb, 0x3, 
       0x2, 0x2, 0x2, 0xcd, 0xce, 0x3, 0x2, 0x2, 0x2, 0xce, 0x5, 0x3, 0x2, 
       0x2, 0x2, 0xcf, 0xec, 0x5, 0x52, 0x2a, 0x2, 0xd0, 0xd1, 0x7, 0xd, 
       0x2, 0x2, 0xd1, 0xec, 0x8, 0x4, 0x1, 0x2, 0xd2, 0xec, 0x5, 0x58, 
       0x2d, 0x2, 0xd3, 0xd4, 0x7, 0xe, 0x2, 0x2, 0xd4, 0xec, 0x8, 0x4, 
       0x1, 0x2, 0xd5, 0xec, 0x5, 0x5a, 0x2e, 0x2, 0xd6, 0xd7, 0x7, 0x14, 
       0x2, 0x2, 0xd7, 0xec, 0x8, 0x4, 0x1, 0x2, 0xd8, 0xec, 0x5, 0x5c, 
       0x2f, 0x2, 0xd9, 0xda, 0x7, 0x15, 0x2, 0x2, 0xda, 0xec, 0x8, 0x4, 
       0x1, 0x2, 0xdb, 0xec, 0x5, 0x5e, 0x30, 0x2, 0xdc, 0xdd, 0x7, 0x16, 
       0x2, 0x2, 0xdd, 0xec, 0x8, 0x4, 0x1, 0x2, 0xde, 0xec, 0x5, 0x60, 
       0x31, 0x2, 0xdf, 0xe0, 0x7, 0x17, 0x2, 0x2, 0xe0, 0xec, 0x8, 0x4, 
       0x1, 0x2, 0xe1, 0xec, 0x5, 0x62, 0x32, 0x2, 0xe2, 0xe3, 0x7, 0x18, 
       0x2, 0x2, 0xe3, 0xec, 0x8, 0x4, 0x1, 0x2, 0xe4, 0xec, 0x5, 0x8, 0x5, 
       0x2, 0xe5, 0xe6, 0x7, 0x19, 0x2, 0x2, 0xe6, 0xec, 0x8, 0x4, 0x1, 
       0x2, 0xe7, 0xec, 0x5, 0x20, 0x11, 0x2, 0xe8, 0xe9, 0x7, 0x1a, 0x2, 
       0x2, 0xe9, 0xec, 0x8, 0x4, 0x1, 0x2, 0xea, 0xec, 0x5, 0xc0, 0x61, 
       0x2, 0xeb, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xd0, 0x3, 0x2, 0x2, 0x2, 
       0xeb, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xd3, 0x3, 0x2, 0x2, 0x2, 0xeb, 
       0xd5, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xd8, 
       0x3, 0x2, 0x2, 0x2, 0xeb, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xdb, 0x3, 
       0x2, 0x2, 0x2, 0xeb, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xde, 0x3, 0x2, 
       0x2, 0x2, 0xeb, 0xdf, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xe1, 0x3, 0x2, 0x2, 
       0x2, 0xeb, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xe4, 0x3, 0x2, 0x2, 0x2, 
       0xeb, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xeb, 
       0xe8, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xea, 0x3, 0x2, 0x2, 0x2, 0xec, 0x7, 
       0x3, 0x2, 0x2, 0x2, 0xed, 0xee, 0x7, 0x19, 0x2, 0x2, 0xee, 0xef, 
       0x8, 0x5, 0x1, 0x2, 0xef, 0xf0, 0x7, 0x65, 0x2, 0x2, 0xf0, 0xf1, 
       0x8, 0x5, 0x1, 0x2, 0xf1, 0xf5, 0x7, 0x3b, 0x2, 0x2, 0xf2, 0xf6, 
       0x5, 0xa, 0x6, 0x2, 0xf3, 0xf4, 0x7, 0x65, 0x2, 0x2, 0xf4, 0xf6, 
       0x8, 0x5, 0x1, 0x2, 0xf5, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xf3, 0x3, 
       0x2, 0x2, 0x2, 0xf6, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xf8, 0x7, 0x35, 
       0x2, 0x2, 0xf8, 0x104, 0x8, 0x5, 0x1, 0x2, 0xf9, 0xfa, 0x5, 0xc, 
       0x7, 0x2, 0xfa, 0x101, 0x8, 0x5, 0x1, 0x2, 0xfb, 0xfc, 0x7, 0x5c, 
       0x2, 0x2, 0xfc, 0xfd, 0x5, 0xc, 0x7, 0x2, 0xfd, 0xfe, 0x8, 0x5, 0x1, 
       0x2, 0xfe, 0x100, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfb, 0x3, 0x2, 0x2, 
       0x2, 0x100, 0x103, 0x3, 0x2, 0x2, 0x2, 0x101, 0xff, 0x3, 0x2, 0x2, 
       0x2, 0x101, 0x102, 0x3, 0x2, 0x2, 0x2, 0x102, 0x105, 0x3, 0x2, 0x2, 
       0x2, 0x103, 0x101, 0x3, 0x2, 0x2, 0x2, 0x104, 0xf9, 0x3, 0x2, 0x2, 
       0x2, 0x104, 0x105, 0x3, 0x2, 0x2, 0x2, 0x105, 0x106, 0x3, 0x2, 0x2, 
       0x2, 0x106, 0x107, 0x7, 0x36, 0x2, 0x2, 0x107, 0x108, 0x8, 0x5, 0x1, 
       0x2, 0x108, 0x109, 0x5, 0x36, 0x1c, 0x2, 0x109, 0x10a, 0x8, 0x5, 
       0x1, 0x2, 0x10a, 0x9, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x10c, 0x7, 0x37, 
       0x2, 0x2, 0x10c, 0x10d, 0x7, 0x65, 0x2, 0x2, 0x10d, 0x10e, 0x7, 0x38, 
       0x2, 0x2, 0x10e, 0xb, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x125, 0x7, 0x6, 
       0x2, 0x2, 0x110, 0x125, 0x7, 0x9, 0x2, 0x2, 0x111, 0x11e, 0x7, 0x37, 
       0x2, 0x2, 0x112, 0x117, 0x5, 0xc, 0x7, 0x2, 0x113, 0x114, 0x7, 0x5c, 
       0x2, 0x2, 0x114, 0x116, 0x5, 0xc, 0x7, 0x2, 0x115, 0x113, 0x3, 0x2, 
       0x2, 0x2, 0x116, 0x119, 0x3, 0x2, 0x2, 0x2, 0x117, 0x115, 0x3, 0x2, 
       0x2, 0x2, 0x117, 0x118, 0x3, 0x2, 0x2, 0x2, 0x118, 0x11c, 0x3, 0x2, 
       0x2, 0x2, 0x119, 0x117, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x11b, 0x7, 0x50, 
       0x2, 0x2, 0x11b, 0x11d, 0x5, 0xc, 0x7, 0x2, 0x11c, 0x11a, 0x3, 0x2, 
       0x2, 0x2, 0x11c, 0x11d, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11f, 0x3, 0x2, 
       0x2, 0x2, 0x11e, 0x112, 0x3, 0x2, 0x2, 0x2, 0x11e, 0x11f, 0x3, 0x2, 
       0x2, 0x2, 0x11f, 0x120, 0x3, 0x2, 0x2, 0x2, 0x120, 0x125, 0x7, 0x38, 
       0x2, 0x2, 0x121, 0x125, 0x5, 0xe, 0x8, 0x2, 0x122, 0x123, 0x8, 0x7, 
       0x1, 0x2, 0x123, 0x125, 0xb, 0x2, 0x2, 0x2, 0x124, 0x10f, 0x3, 0x2, 
       0x2, 0x2, 0x124, 0x110, 0x3, 0x2, 0x2, 0x2, 0x124, 0x111, 0x3, 0x2, 
       0x2, 0x2, 0x124, 0x121, 0x3, 0x2, 0x2, 0x2, 0x124, 0x122, 0x3, 0x2, 
       0x2, 0x2, 0x125, 0xd, 0x3, 0x2, 0x2, 0x2, 0x126, 0x12b, 0x5, 0x10, 
       0x9, 0x2, 0x127, 0x128, 0x7, 0x3f, 0x2, 0x2, 0x128, 0x12a, 0x5, 0x10, 
       0x9, 0x2, 0x129, 0x127, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12d, 0x3, 0x2, 
       0x2, 0x2, 0x12b, 0x129, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x12c, 0x3, 0x2, 
       0x2, 0x2, 0x12c, 0xf, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x12b, 0x3, 0x2, 
       0x2, 0x2, 0x12e, 0x133, 0x5, 0x12, 0xa, 0x2, 0x12f, 0x130, 0x7, 0x3e, 
       0x2, 0x2, 0x130, 0x132, 0x5, 0x12, 0xa, 0x2, 0x131, 0x12f, 0x3, 0x2, 
       0x2, 0x2, 0x132, 0x135, 0x3, 0x2, 0x2, 0x2, 0x133, 0x131, 0x3, 0x2, 
       0x2, 0x2, 0x133, 0x134, 0x3, 0x2, 0x2, 0x2, 0x134, 0x11, 0x3, 0x2, 
       0x2, 0x2, 0x135, 0x133, 0x3, 0x2, 0x2, 0x2, 0x136, 0x13b, 0x5, 0x14, 
       0xb, 0x2, 0x137, 0x138, 0x9, 0x2, 0x2, 0x2, 0x138, 0x13a, 0x5, 0x14, 
       0xb, 0x2, 0x139, 0x137, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x13d, 0x3, 0x2, 
       0x2, 0x2, 0x13b, 0x139, 0x3, 0x2, 0x2, 0x2, 0x13b, 0x13c, 0x3, 0x2, 
       0x2, 0x2, 0x13c, 0x13, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x13b, 0x3, 0x2, 
       0x2, 0x2, 0x13e, 0x143, 0x5, 0x16, 0xc, 0x2, 0x13f, 0x140, 0x9, 0x3, 
       0x2, 0x2, 0x140, 0x142, 0x5, 0x16, 0xc, 0x2, 0x141, 0x13f, 0x3, 0x2, 
       0x2, 0x2, 0x142, 0x145, 0x3, 0x2, 0x2, 0x2, 0x143, 0x141, 0x3, 0x2, 
       0x2, 0x2, 0x143, 0x144, 0x3, 0x2, 0x2, 0x2, 0x144, 0x15, 0x3, 0x2, 
       0x2, 0x2, 0x145, 0x143, 0x3, 0x2, 0x2, 0x2, 0x146, 0x14b, 0x5, 0x18, 
       0xd, 0x2, 0x147, 0x148, 0x9, 0x4, 0x2, 0x2, 0x148, 0x14a, 0x5, 0x18, 
       0xd, 0x2, 0x149, 0x147, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x14d, 0x3, 0x2, 
       0x2, 0x2, 0x14b, 0x149, 0x3, 0x2, 0x2, 0x2, 0x14b, 0x14c, 0x3, 0x2, 
       0x2, 0x2, 0x14c, 0x17, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x14b, 0x3, 0x2, 
       0x2, 0x2, 0x14e, 0x163, 0x7, 0x8, 0x2, 0x2, 0x14f, 0x163, 0x7, 0x6, 
       0x2, 0x2, 0x150, 0x163, 0x7, 0x9, 0x2, 0x2, 0x151, 0x163, 0x7, 0x5, 
       0x2, 0x2, 0x152, 0x163, 0x7, 0x7, 0x2, 0x2, 0x153, 0x163, 0x7, 0x1e, 
       0x2, 0x2, 0x154, 0x163, 0x7, 0x24, 0x2, 0x2, 0x155, 0x156, 0x7, 0x35, 
       0x2, 0x2, 0x156, 0x157, 0x5, 0xe, 0x8, 0x2, 0x157, 0x158, 0x7, 0x36, 
       0x2, 0x2, 0x158, 0x163, 0x3, 0x2, 0x2, 0x2, 0x159, 0x163, 0x5, 0x1a, 
       0xe, 0x2, 0x15a, 0x160, 0x7, 0x65, 0x2, 0x2, 0x15b, 0x15d, 0x7, 0x35, 
       0x2, 0x2, 0x15c, 0x15e, 0x5, 0x1e, 0x10, 0x2, 0x15d, 0x15c, 0x3, 
       0x2, 0x2, 0x2, 0x15d, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x15f, 0x3, 
       0x2, 0x2, 0x2, 0x15f, 0x161, 0x7, 0x36, 0x2, 0x2, 0x160, 0x15b, 0x3, 
       0x2, 0x2, 0x2, 0x160, 0x161, 0x3, 0x2, 0x2, 0x2, 0x161, 0x163, 0x3, 
       0x2, 0x2, 0x2, 0x162, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x162, 0x14f, 0x3, 
       0x2, 0x2, 0x2, 0x162, 0x150, 0x3, 0x2, 0x2, 0x2, 0x162, 0x151, 0x3, 
       0x2, 0x2, 0x2, 0x162, 0x152, 0x3, 0x2, 0x2, 0x2, 0x162, 0x153, 0x3, 
       0x2, 0x2, 0x2, 0x162, 0x154, 0x3, 0x2, 0x2, 0x2, 0x162, 0x155, 0x3, 
       0x2, 0x2, 0x2, 0x162, 0x159, 0x3, 0x2, 0x2, 0x2, 0x162, 0x15a, 0x3, 
       0x2, 0x2, 0x2, 0x163, 0x19, 0x3, 0x2, 0x2, 0x2, 0x164, 0x166, 0x9, 
       0x5, 0x2, 0x2, 0x165, 0x164, 0x3, 0x2, 0x2, 0x2, 0x165, 0x166, 0x3, 
       0x2, 0x2, 0x2, 0x166, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x167, 0x168, 0x7, 
       0x65, 0x2, 0x2, 0x168, 0x16b, 0x8, 0xe, 0x1, 0x2, 0x169, 0x16b, 0x7, 
       0x4b, 0x2, 0x2, 0x16a, 0x167, 0x3, 0x2, 0x2, 0x2, 0x16a, 0x169, 0x3, 
       0x2, 0x2, 0x2, 0x16b, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x16e, 0x5, 
       0x1c, 0xf, 0x2, 0x16d, 0x16c, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x16e, 0x3, 
       0x2, 0x2, 0x2, 0x16e, 0x17a, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x173, 0x9, 
       0x5, 0x2, 0x2, 0x170, 0x171, 0x7, 0x65, 0x2, 0x2, 0x171, 0x174, 0x8, 
       0xe, 0x1, 0x2, 0x172, 0x174, 0x7, 0x4b, 0x2, 0x2, 0x173, 0x170, 0x3, 
       0x2, 0x2, 0x2, 0x173, 0x172, 0x3, 0x2, 0x2, 0x2, 0x174, 0x176, 0x3, 
       0x2, 0x2, 0x2, 0x175, 0x177, 0x5, 0x1c, 0xf, 0x2, 0x176, 0x175, 0x3, 
       0x2, 0x2, 0x2, 0x176, 0x177, 0x3, 0x2, 0x2, 0x2, 0x177, 0x179, 0x3, 
       0x2, 0x2, 0x2, 0x178, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x179, 0x17c, 0x3, 
       0x2, 0x2, 0x2, 0x17a, 0x178, 0x3, 0x2, 0x2, 0x2, 0x17a, 0x17b, 0x3, 
       0x2, 0x2, 0x2, 0x17b, 0x17d, 0x3, 0x2, 0x2, 0x2, 0x17c, 0x17a, 0x3, 
       0x2, 0x2, 0x2, 0x17d, 0x185, 0x9, 0x5, 0x2, 0x2, 0x17e, 0x17f, 0x7, 
       0x65, 0x2, 0x2, 0x17f, 0x182, 0x8, 0xe, 0x1, 0x2, 0x180, 0x182, 0x7, 
       0x4b, 0x2, 0x2, 0x181, 0x17e, 0x3, 0x2, 0x2, 0x2, 0x181, 0x180, 0x3, 
       0x2, 0x2, 0x2, 0x182, 0x186, 0x3, 0x2, 0x2, 0x2, 0x183, 0x186, 0x7, 
       0x1e, 0x2, 0x2, 0x184, 0x186, 0x7, 0x24, 0x2, 0x2, 0x185, 0x181, 
       0x3, 0x2, 0x2, 0x2, 0x185, 0x183, 0x3, 0x2, 0x2, 0x2, 0x185, 0x184, 
       0x3, 0x2, 0x2, 0x2, 0x186, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x187, 0x188, 
       0x7, 0x37, 0x2, 0x2, 0x188, 0x189, 0x5, 0xe, 0x8, 0x2, 0x189, 0x18a, 
       0x7, 0x38, 0x2, 0x2, 0x18a, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x18b, 0x190, 
       0x5, 0xe, 0x8, 0x2, 0x18c, 0x18d, 0x7, 0x5c, 0x2, 0x2, 0x18d, 0x18f, 
       0x5, 0xe, 0x8, 0x2, 0x18e, 0x18c, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x192, 
       0x3, 0x2, 0x2, 0x2, 0x190, 0x18e, 0x3, 0x2, 0x2, 0x2, 0x190, 0x191, 
       0x3, 0x2, 0x2, 0x2, 0x191, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x192, 0x190, 
       0x3, 0x2, 0x2, 0x2, 0x193, 0x194, 0x7, 0x1a, 0x2, 0x2, 0x194, 0x195, 
       0x7, 0x65, 0x2, 0x2, 0x195, 0x1a2, 0x8, 0x11, 0x1, 0x2, 0x196, 0x19f, 
       0x7, 0x35, 0x2, 0x2, 0x197, 0x19c, 0x5, 0x22, 0x12, 0x2, 0x198, 0x199, 
       0x7, 0x5c, 0x2, 0x2, 0x199, 0x19b, 0x5, 0x22, 0x12, 0x2, 0x19a, 0x198, 
       0x3, 0x2, 0x2, 0x2, 0x19b, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19a, 
       0x3, 0x2, 0x2, 0x2, 0x19c, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x19d, 0x1a0, 
       0x3, 0x2, 0x2, 0x2, 0x19e, 0x19c, 0x3, 0x2, 0x2, 0x2, 0x19f, 0x197, 
       0x3, 0x2, 0x2, 0x2, 0x19f, 0x1a0, 0x3, 0x2, 0x2, 0x2, 0x1a0, 0x1a1, 
       0x3, 0x2, 0x2, 0x2, 0x1a1, 0x1a3, 0x7, 0x36, 0x2, 0x2, 0x1a2, 0x196, 
       0x3, 0x2, 0x2, 0x2, 0x1a2, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a4, 
       0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a5, 0x7, 0x39, 0x2, 0x2, 0x1a5, 0x1a6, 
       0x7, 0x70, 0x2, 0x2, 0x1a6, 0x1a7, 0x5, 0x24, 0x13, 0x2, 0x1a7, 0x1a8, 
       0x7, 0x3a, 0x2, 0x2, 0x1a8, 0x1a9, 0x7, 0x70, 0x2, 0x2, 0x1a9, 0x21, 
       0x3, 0x2, 0x2, 0x2, 0x1aa, 0x1ac, 0x7, 0x4f, 0x2, 0x2, 0x1ab, 0x1aa, 
       0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1ac, 0x3, 0x2, 0x2, 0x2, 0x1ac, 0x1ad, 
       0x3, 0x2, 0x2, 0x2, 0x1ad, 0x1ae, 0x7, 0x47, 0x2, 0x2, 0x1ae, 0x1af, 
       0x7, 0x65, 0x2, 0x2, 0x1af, 0x23, 0x3, 0x2, 0x2, 0x2, 0x1b0, 0x1bb, 
       0x5, 0x26, 0x14, 0x2, 0x1b1, 0x1b3, 0x7, 0x70, 0x2, 0x2, 0x1b2, 0x1b1, 
       0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1b4, 
       0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b6, 0x7, 0x3f, 0x2, 0x2, 0x1b5, 0x1b7, 
       0x7, 0x70, 0x2, 0x2, 0x1b6, 0x1b5, 0x3, 0x2, 0x2, 0x2, 0x1b6, 0x1b7, 
       0x3, 0x2, 0x2, 0x2, 0x1b7, 0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1b8, 0x1ba, 
       0x5, 0x26, 0x14, 0x2, 0x1b9, 0x1b2, 0x3, 0x2, 0x2, 0x2, 0x1ba, 0x1bd, 
       0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1b9, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1bc, 
       0x3, 0x2, 0x2, 0x2, 0x1bc, 0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1bd, 0x1bb, 
       0x3, 0x2, 0x2, 0x2, 0x1be, 0x1c0, 0x7, 0x70, 0x2, 0x2, 0x1bf, 0x1be, 
       0x3, 0x2, 0x2, 0x2, 0x1bf, 0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x25, 
       0x3, 0x2, 0x2, 0x2, 0x1c1, 0x1cc, 0x5, 0x28, 0x15, 0x2, 0x1c2, 0x1c4, 
       0x7, 0x70, 0x2, 0x2, 0x1c3, 0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c4, 
       0x3, 0x2, 0x2, 0x2, 0x1c4, 0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c5, 0x1c7, 
       0x7, 0x3e, 0x2, 0x2, 0x1c6, 0x1c8, 0x7, 0x70, 0x2, 0x2, 0x1c7, 0x1c6, 
       0x3, 0x2, 0x2, 0x2, 0x1c7, 0x1c8, 0x3, 0x2, 0x2, 0x2, 0x1c8, 0x1c9, 
       0x3, 0x2, 0x2, 0x2, 0x1c9, 0x1cb, 0x5, 0x28, 0x15, 0x2, 0x1ca, 0x1c3, 
       0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1ce, 0x3, 0x2, 0x2, 0x2, 0x1cc, 0x1ca, 
       0x3, 0x2, 0x2, 0x2, 0x1cc, 0x1cd, 0x3, 0x2, 0x2, 0x2, 0x1cd, 0x1d0, 
       0x3, 0x2, 0x2, 0x2, 0x1ce, 0x1cc, 0x3, 0x2, 0x2, 0x2, 0x1cf, 0x1d1, 
       0x7, 0x70, 0x2, 0x2, 0x1d0, 0x1cf, 0x3, 0x2, 0x2, 0x2, 0x1d0, 0x1d1, 
       0x3, 0x2, 0x2, 0x2, 0x1d1, 0x27, 0x3, 0x2, 0x2, 0x2, 0x1d2, 0x1dd, 
       0x5, 0x2a, 0x16, 0x2, 0x1d3, 0x1d5, 0x7, 0x70, 0x2, 0x2, 0x1d4, 0x1d3, 
       0x3, 0x2, 0x2, 0x2, 0x1d4, 0x1d5, 0x3, 0x2, 0x2, 0x2, 0x1d5, 0x1d6, 
       0x3, 0x2, 0x2, 0x2, 0x1d6, 0x1d8, 0x9, 0x2, 0x2, 0x2, 0x1d7, 0x1d9, 
       0x7, 0x70, 0x2, 0x2, 0x1d8, 0x1d7, 0x3, 0x2, 0x2, 0x2, 0x1d8, 0x1d9, 
       0x3, 0x2, 0x2, 0x2, 0x1d9, 0x1da, 0x3, 0x2, 0x2, 0x2, 0x1da, 0x1dc, 
       0x5, 0x2a, 0x16, 0x2, 0x1db, 0x1d4, 0x3, 0x2, 0x2, 0x2, 0x1dc, 0x1df, 
       0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1db, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1de, 
       0x3, 0x2, 0x2, 0x2, 0x1de, 0x1e1, 0x3, 0x2, 0x2, 0x2, 0x1df, 0x1dd, 
       0x3, 0x2, 0x2, 0x2, 0x1e0, 0x1e2, 0x7, 0x70, 0x2, 0x2, 0x1e1, 0x1e0, 
       0x3, 0x2, 0x2, 0x2, 0x1e1, 0x1e2, 0x3, 0x2, 0x2, 0x2, 0x1e2, 0x29, 
       0x3, 0x2, 0x2, 0x2, 0x1e3, 0x1ee, 0x5, 0x2c, 0x17, 0x2, 0x1e4, 0x1e6, 
       0x7, 0x70, 0x2, 0x2, 0x1e5, 0x1e4, 0x3, 0x2, 0x2, 0x2, 0x1e5, 0x1e6, 
       0x3, 0x2, 0x2, 0x2, 0x1e6, 0x1e7, 0x3, 0x2, 0x2, 0x2, 0x1e7, 0x1e9, 
       0x9, 0x3, 0x2, 0x2, 0x1e8, 0x1ea, 0x7, 0x70, 0x2, 0x2, 0x1e9, 0x1e8, 
       0x3, 0x2, 0x2, 0x2, 0x1e9, 0x1ea, 0x3, 0x2, 0x2, 0x2, 0x1ea, 0x1eb, 
       0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1ed, 0x5, 0x2c, 0x17, 0x2, 0x1ec, 0x1e5, 
       0x3, 0x2, 0x2, 0x2, 0x1ed, 0x1f0, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1ec, 
       0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1ef, 0x3, 0x2, 0x2, 0x2, 0x1ef, 0x1f2, 
       0x3, 0x2, 0x2, 0x2, 0x1f0, 0x1ee, 0x3, 0x2, 0x2, 0x2, 0x1f1, 0x1f3, 
       0x7, 0x70, 0x2, 0x2, 0x1f2, 0x1f1, 0x3, 0x2, 0x2, 0x2, 0x1f2, 0x1f3, 
       0x3, 0x2, 0x2, 0x2, 0x1f3, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x1f4, 0x1ff, 
       0x5, 0x2e, 0x18, 0x2, 0x1f5, 0x1f7, 0x7, 0x70, 0x2, 0x2, 0x1f6, 0x1f5, 
       0x3, 0x2, 0x2, 0x2, 0x1f6, 0x1f7, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1f8, 
       0x3, 0x2, 0x2, 0x2, 0x1f8, 0x1fa, 0x9, 0x4, 0x2, 0x2, 0x1f9, 0x1fb, 
       0x7, 0x70, 0x2, 0x2, 0x1fa, 0x1f9, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fb, 
       0x3, 0x2, 0x2, 0x2, 0x1fb, 0x1fc, 0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1fe, 
       0x5, 0x2e, 0x18, 0x2, 0x1fd, 0x1f6, 0x3, 0x2, 0x2, 0x2, 0x1fe, 0x201, 
       0x3, 0x2, 0x2, 0x2, 0x1ff, 0x1fd, 0x3, 0x2, 0x2, 0x2, 0x1ff, 0x200, 
       0x3, 0x2, 0x2, 0x2, 0x200, 0x203, 0x3, 0x2, 0x2, 0x2, 0x201, 0x1ff, 
       0x3, 0x2, 0x2, 0x2, 0x202, 0x204, 0x7, 0x70, 0x2, 0x2, 0x203, 0x202, 
       0x3, 0x2, 0x2, 0x2, 0x203, 0x204, 0x3, 0x2, 0x2, 0x2, 0x204, 0x2d, 
       0x3, 0x2, 0x2, 0x2, 0x205, 0x233, 0x7, 0x8, 0x2, 0x2, 0x206, 0x233, 
       0x7, 0x6, 0x2, 0x2, 0x207, 0x233, 0x7, 0x9, 0x2, 0x2, 0x208, 0x233, 
       0x7, 0x5, 0x2, 0x2, 0x209, 0x233, 0x7, 0x7, 0x2, 0x2, 0x20a, 0x233, 
       0x7, 0x1e, 0x2, 0x2, 0x20b, 0x20c, 0x7, 0x40, 0x2, 0x2, 0x20c, 0x233, 
       0x7, 0x65, 0x2, 0x2, 0x20d, 0x233, 0x7, 0x24, 0x2, 0x2, 0x20e, 0x210, 
       0x7, 0x35, 0x2, 0x2, 0x20f, 0x211, 0x7, 0x70, 0x2, 0x2, 0x210, 0x20f, 
       0x3, 0x2, 0x2, 0x2, 0x210, 0x211, 0x3, 0x2, 0x2, 0x2, 0x211, 0x212, 
       0x3, 0x2, 0x2, 0x2, 0x212, 0x214, 0x5, 0x24, 0x13, 0x2, 0x213, 0x215, 
       0x7, 0x70, 0x2, 0x2, 0x214, 0x213, 0x3, 0x2, 0x2, 0x2, 0x214, 0x215, 
       0x3, 0x2, 0x2, 0x2, 0x215, 0x216, 0x3, 0x2, 0x2, 0x2, 0x216, 0x218, 
       0x7, 0x36, 0x2, 0x2, 0x217, 0x219, 0x7, 0x70, 0x2, 0x2, 0x218, 0x217, 
       0x3, 0x2, 0x2, 0x2, 0x218, 0x219, 0x3, 0x2, 0x2, 0x2, 0x219, 0x233, 
       0x3, 0x2, 0x2, 0x2, 0x21a, 0x21c, 0x7, 0x65, 0x2, 0x2, 0x21b, 0x21d, 
       0x7, 0x70, 0x2, 0x2, 0x21c, 0x21b, 0x3, 0x2, 0x2, 0x2, 0x21c, 0x21d, 
       0x3, 0x2, 0x2, 0x2, 0x21d, 0x21e, 0x3, 0x2, 0x2, 0x2, 0x21e, 0x220, 
       0x7, 0x35, 0x2, 0x2, 0x21f, 0x221, 0x7, 0x70, 0x2, 0x2, 0x220, 0x21f, 
       0x3, 0x2, 0x2, 0x2, 0x220, 0x221, 0x3, 0x2, 0x2, 0x2, 0x221, 0x223, 
       0x3, 0x2, 0x2, 0x2, 0x222, 0x224, 0x5, 0x34, 0x1b, 0x2, 0x223, 0x222, 
       0x3, 0x2, 0x2, 0x2, 0x223, 0x224, 0x3, 0x2, 0x2, 0x2, 0x224, 0x226, 
       0x3, 0x2, 0x2, 0x2, 0x225, 0x227, 0x7, 0x70, 0x2, 0x2, 0x226, 0x225, 
       0x3, 0x2, 0x2, 0x2, 0x226, 0x227, 0x3, 0x2, 0x2, 0x2, 0x227, 0x228, 
       0x3, 0x2, 0x2, 0x2, 0x228, 0x22a, 0x7, 0x36, 0x2, 0x2, 0x229, 0x22b, 
       0x7, 0x70, 0x2, 0x2, 0x22a, 0x229, 0x3, 0x2, 0x2, 0x2, 0x22a, 0x22b, 
       0x3, 0x2, 0x2, 0x2, 0x22b, 0x233, 0x3, 0x2, 0x2, 0x2, 0x22c, 0x22e, 
       0x5, 0x30, 0x19, 0x2, 0x22d, 0x22f, 0x7, 0x70, 0x2, 0x2, 0x22e, 0x22d, 
       0x3, 0x2, 0x2, 0x2, 0x22e, 0x22f, 0x3, 0x2, 0x2, 0x2, 0x22f, 0x233, 
       0x3, 0x2, 0x2, 0x2, 0x230, 0x231, 0x7, 0x47, 0x2, 0x2, 0x231, 0x233, 
       0x7, 0x65, 0x2, 0x2, 0x232, 0x205, 0x3, 0x2, 0x2, 0x2, 0x232, 0x206, 
       0x3, 0x2, 0x2, 0x2, 0x232, 0x207, 0x3, 0x2, 0x2, 0x2, 0x232, 0x208, 
       0x3, 0x2, 0x2, 0x2, 0x232, 0x209, 0x3, 0x2, 0x2, 0x2, 0x232, 0x20a, 
       0x3, 0x2, 0x2, 0x2, 0x232, 0x20b, 0x3, 0x2, 0x2, 0x2, 0x232, 0x20d, 
       0x3, 0x2, 0x2, 0x2, 0x232, 0x20e, 0x3, 0x2, 0x2, 0x2, 0x232, 0x21a, 
       0x3, 0x2, 0x2, 0x2, 0x232, 0x22c, 0x3, 0x2, 0x2, 0x2, 0x232, 0x230, 
       0x3, 0x2, 0x2, 0x2, 0x233, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x234, 0x236, 
       0x9, 0x5, 0x2, 0x2, 0x235, 0x234, 0x3, 0x2, 0x2, 0x2, 0x235, 0x236, 
       0x3, 0x2, 0x2, 0x2, 0x236, 0x238, 0x3, 0x2, 0x2, 0x2, 0x237, 0x239, 
       0x7, 0x70, 0x2, 0x2, 0x238, 0x237, 0x3, 0x2, 0x2, 0x2, 0x238, 0x239, 
       0x3, 0x2, 0x2, 0x2, 0x239, 0x23a, 0x3, 0x2, 0x2, 0x2, 0x23a, 0x23c, 
       0x9, 0x6, 0x2, 0x2, 0x23b, 0x23d, 0x7, 0x70, 0x2, 0x2, 0x23c, 0x23b, 
       0x3, 0x2, 0x2, 0x2, 0x23c, 0x23d, 0x3, 0x2, 0x2, 0x2, 0x23d, 0x23f, 
       0x3, 0x2, 0x2, 0x2, 0x23e, 0x240, 0x5, 0x32, 0x1a, 0x2, 0x23f, 0x23e, 
       0x3, 0x2, 0x2, 0x2, 0x23f, 0x240, 0x3, 0x2, 0x2, 0x2, 0x240, 0x24e, 
       0x3, 0x2, 0x2, 0x2, 0x241, 0x243, 0x9, 0x5, 0x2, 0x2, 0x242, 0x244, 
       0x7, 0x70, 0x2, 0x2, 0x243, 0x242, 0x3, 0x2, 0x2, 0x2, 0x243, 0x244, 
       0x3, 0x2, 0x2, 0x2, 0x244, 0x245, 0x3, 0x2, 0x2, 0x2, 0x245, 0x247, 
       0x9, 0x6, 0x2, 0x2, 0x246, 0x248, 0x7, 0x70, 0x2, 0x2, 0x247, 0x246, 
       0x3, 0x2, 0x2, 0x2, 0x247, 0x248, 0x3, 0x2, 0x2, 0x2, 0x248, 0x24a, 
       0x3, 0x2, 0x2, 0x2, 0x249, 0x24b, 0x5, 0x32, 0x1a, 0x2, 0x24a, 0x249, 
       0x3, 0x2, 0x2, 0x2, 0x24a, 0x24b, 0x3, 0x2, 0x2, 0x2, 0x24b, 0x24d, 
       0x3, 0x2, 0x2, 0x2, 0x24c, 0x241, 0x3, 0x2, 0x2, 0x2, 0x24d, 0x250, 
       0x3, 0x2, 0x2, 0x2, 0x24e, 0x24c, 0x3, 0x2, 0x2, 0x2, 0x24e, 0x24f, 
       0x3, 0x2, 0x2, 0x2, 0x24f, 0x25c, 0x3, 0x2, 0x2, 0x2, 0x250, 0x24e, 
       0x3, 0x2, 0x2, 0x2, 0x251, 0x253, 0x9, 0x5, 0x2, 0x2, 0x252, 0x254, 
       0x7, 0x70, 0x2, 0x2, 0x253, 0x252, 0x3, 0x2, 0x2, 0x2, 0x253, 0x254, 
       0x3, 0x2, 0x2, 0x2, 0x254, 0x25a, 0x3, 0x2, 0x2, 0x2, 0x255, 0x25b, 
       0x9, 0x6, 0x2, 0x2, 0x256, 0x25b, 0x7, 0x1e, 0x2, 0x2, 0x257, 0x258, 
       0x7, 0x40, 0x2, 0x2, 0x258, 0x25b, 0x7, 0x65, 0x2, 0x2, 0x259, 0x25b, 
       0x7, 0x24, 0x2, 0x2, 0x25a, 0x255, 0x3, 0x2, 0x2, 0x2, 0x25a, 0x256, 
       0x3, 0x2, 0x2, 0x2, 0x25a, 0x257, 0x3, 0x2, 0x2, 0x2, 0x25a, 0x259, 
       0x3, 0x2, 0x2, 0x2, 0x25b, 0x25d, 0x3, 0x2, 0x2, 0x2, 0x25c, 0x251, 
       0x3, 0x2, 0x2, 0x2, 0x25c, 0x25d, 0x3, 0x2, 0x2, 0x2, 0x25d, 0x31, 
       0x3, 0x2, 0x2, 0x2, 0x25e, 0x260, 0x7, 0x37, 0x2, 0x2, 0x25f, 0x261, 
       0x7, 0x70, 0x2, 0x2, 0x260, 0x25f, 0x3, 0x2, 0x2, 0x2, 0x260, 0x261, 
       0x3, 0x2, 0x2, 0x2, 0x261, 0x262, 0x3, 0x2, 0x2, 0x2, 0x262, 0x264, 
       0x5, 0x24, 0x13, 0x2, 0x263, 0x265, 0x7, 0x70, 0x2, 0x2, 0x264, 0x263, 
       0x3, 0x2, 0x2, 0x2, 0x264, 0x265, 0x3, 0x2, 0x2, 0x2, 0x265, 0x266, 
       0x3, 0x2, 0x2, 0x2, 0x266, 0x267, 0x7, 0x38, 0x2, 0x2, 0x267, 0x33, 
       0x3, 0x2, 0x2, 0x2, 0x268, 0x273, 0x5, 0x24, 0x13, 0x2, 0x269, 0x26b, 
       0x7, 0x70, 0x2, 0x2, 0x26a, 0x269, 0x3, 0x2, 0x2, 0x2, 0x26a, 0x26b, 
       0x3, 0x2, 0x2, 0x2, 0x26b, 0x26c, 0x3, 0x2, 0x2, 0x2, 0x26c, 0x26e, 
       0x7, 0x5c, 0x2, 0x2, 0x26d, 0x26f, 0x7, 0x70, 0x2, 0x2, 0x26e, 0x26d, 
       0x3, 0x2, 0x2, 0x2, 0x26e, 0x26f, 0x3, 0x2, 0x2, 0x2, 0x26f, 0x270, 
       0x3, 0x2, 0x2, 0x2, 0x270, 0x272, 0x5, 0x24, 0x13, 0x2, 0x271, 0x26a, 
       0x3, 0x2, 0x2, 0x2, 0x272, 0x275, 0x3, 0x2, 0x2, 0x2, 0x273, 0x271, 
       0x3, 0x2, 0x2, 0x2, 0x273, 0x274, 0x3, 0x2, 0x2, 0x2, 0x274, 0x277, 
       0x3, 0x2, 0x2, 0x2, 0x275, 0x273, 0x3, 0x2, 0x2, 0x2, 0x276, 0x278, 
       0x7, 0x70, 0x2, 0x2, 0x277, 0x276, 0x3, 0x2, 0x2, 0x2, 0x277, 0x278, 
       0x3, 0x2, 0x2, 0x2, 0x278, 0x35, 0x3, 0x2, 0x2, 0x2, 0x279, 0x27a, 
       0x7, 0x39, 0x2, 0x2, 0x27a, 0x27e, 0x7, 0x70, 0x2, 0x2, 0x27b, 0x27d, 
       0x5, 0x38, 0x1d, 0x2, 0x27c, 0x27b, 0x3, 0x2, 0x2, 0x2, 0x27d, 0x280, 
       0x3, 0x2, 0x2, 0x2, 0x27e, 0x27c, 0x3, 0x2, 0x2, 0x2, 0x27e, 0x27f, 
       0x3, 0x2, 0x2, 0x2, 0x27f, 0x28b, 0x3, 0x2, 0x2, 0x2, 0x280, 0x27e, 
       0x3, 0x2, 0x2, 0x2, 0x281, 0x282, 0x7, 0x2b, 0x2, 0x2, 0x282, 0x286, 
       0x7, 0x70, 0x2, 0x2, 0x283, 0x285, 0x5, 0x38, 0x1d, 0x2, 0x284, 0x283, 
       0x3, 0x2, 0x2, 0x2, 0x285, 0x288, 0x3, 0x2, 0x2, 0x2, 0x286, 0x284, 
       0x3, 0x2, 0x2, 0x2, 0x286, 0x287, 0x3, 0x2, 0x2, 0x2, 0x287, 0x289, 
       0x3, 0x2, 0x2, 0x2, 0x288, 0x286, 0x3, 0x2, 0x2, 0x2, 0x289, 0x28a, 
       0x7, 0x2c, 0x2, 0x2, 0x28a, 0x28c, 0x7, 0x70, 0x2, 0x2, 0x28b, 0x281, 
       0x3, 0x2, 0x2, 0x2, 0x28b, 0x28c, 0x3, 0x2, 0x2, 0x2, 0x28c, 0x290, 
       0x3, 0x2, 0x2, 0x2, 0x28d, 0x28f, 0x5, 0x38, 0x1d, 0x2, 0x28e, 0x28d, 
       0x3, 0x2, 0x2, 0x2, 0x28f, 0x292, 0x3, 0x2, 0x2, 0x2, 0x290, 0x28e, 
       0x3, 0x2, 0x2, 0x2, 0x290, 0x291, 0x3, 0x2, 0x2, 0x2, 0x291, 0x293, 
       0x3, 0x2, 0x2, 0x2, 0x292, 0x290, 0x3, 0x2, 0x2, 0x2, 0x293, 0x294, 
       0x7, 0x3a, 0x2, 0x2, 0x294, 0x295, 0x7, 0x61, 0x2, 0x2, 0x295, 0x296, 
       0x7, 0x70, 0x2, 0x2, 0x296, 0x37, 0x3, 0x2, 0x2, 0x2, 0x297, 0x299, 
       0x5, 0x3a, 0x1e, 0x2, 0x298, 0x297, 0x3, 0x2, 0x2, 0x2, 0x298, 0x299, 
       0x3, 0x2, 0x2, 0x2, 0x299, 0x29a, 0x3, 0x2, 0x2, 0x2, 0x29a, 0x29b, 
       0x7, 0x70, 0x2, 0x2, 0x29b, 0x39, 0x3, 0x2, 0x2, 0x2, 0x29c, 0x2ab, 
       0x6, 0x1e, 0x2, 0x2, 0x29d, 0x2a2, 0x7, 0x35, 0x2, 0x2, 0x29e, 0x2a1, 
       0x5, 0x3a, 0x1e, 0x2, 0x29f, 0x2a1, 0x7, 0x70, 0x2, 0x2, 0x2a0, 0x29e, 
       0x3, 0x2, 0x2, 0x2, 0x2a0, 0x29f, 0x3, 0x2, 0x2, 0x2, 0x2a1, 0x2a4, 
       0x3, 0x2, 0x2, 0x2, 0x2a2, 0x2a0, 0x3, 0x2, 0x2, 0x2, 0x2a2, 0x2a3, 
       0x3, 0x2, 0x2, 0x2, 0x2a3, 0x2a7, 0x3, 0x2, 0x2, 0x2, 0x2a4, 0x2a2, 
       0x3, 0x2, 0x2, 0x2, 0x2a5, 0x2a8, 0x5, 0x3c, 0x1f, 0x2, 0x2a6, 0x2a8, 
       0x7, 0x36, 0x2, 0x2, 0x2a7, 0x2a5, 0x3, 0x2, 0x2, 0x2, 0x2a7, 0x2a6, 
       0x3, 0x2, 0x2, 0x2, 0x2a8, 0x2ac, 0x3, 0x2, 0x2, 0x2, 0x2a9, 0x2ac, 
       0x7, 0x4, 0x2, 0x2, 0x2aa, 0x2ac, 0x7, 0x3, 0x2, 0x2, 0x2ab, 0x29d, 
       0x3, 0x2, 0x2, 0x2, 0x2ab, 0x2a9, 0x3, 0x2, 0x2, 0x2, 0x2ab, 0x2aa, 
       0x3, 0x2, 0x2, 0x2, 0x2ac, 0x2ae, 0x3, 0x2, 0x2, 0x2, 0x2ad, 0x2af, 
       0x5, 0x3a, 0x1e, 0x2, 0x2ae, 0x2ad, 0x3, 0x2, 0x2, 0x2, 0x2ae, 0x2af, 
       0x3, 0x2, 0x2, 0x2, 0x2af, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x2b0, 0x2b5, 
       0x5, 0x3e, 0x20, 0x2, 0x2b1, 0x2b5, 0x5, 0x40, 0x21, 0x2, 0x2b2, 
       0x2b5, 0x5, 0x42, 0x22, 0x2, 0x2b3, 0x2b5, 0x5, 0x44, 0x23, 0x2, 
       0x2b4, 0x2b0, 0x3, 0x2, 0x2, 0x2, 0x2b4, 0x2b1, 0x3, 0x2, 0x2, 0x2, 
       0x2b4, 0x2b2, 0x3, 0x2, 0x2, 0x2, 0x2b4, 0x2b3, 0x3, 0x2, 0x2, 0x2, 
       0x2b5, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x2b6, 0x2b7, 0x7, 0x31, 0x2, 0x2, 
       0x2b7, 0x2c2, 0x7, 0x65, 0x2, 0x2, 0x2b8, 0x2b9, 0x7, 0x62, 0x2, 
       0x2, 0x2b9, 0x2ba, 0x7, 0x65, 0x2, 0x2, 0x2ba, 0x2bb, 0x7, 0x39, 
       0x2, 0x2, 0x2bb, 0x2bc, 0x7, 0x65, 0x2, 0x2, 0x2bc, 0x2bd, 0x7, 0x3a, 
       0x2, 0x2, 0x2bd, 0x2be, 0x7, 0x3a, 0x2, 0x2, 0x2be, 0x2c3, 0x8, 0x20, 
       0x1, 0x2, 0x2bf, 0x2c0, 0x7, 0x3a, 0x2, 0x2, 0x2c0, 0x2c3, 0x8, 0x20, 
       0x1, 0x2, 0x2c1, 0x2c3, 0x8, 0x20, 0x1, 0x2, 0x2c2, 0x2b8, 0x3, 0x2, 
       0x2, 0x2, 0x2c2, 0x2bf, 0x3, 0x2, 0x2, 0x2, 0x2c2, 0x2c1, 0x3, 0x2, 
       0x2, 0x2, 0x2c3, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x2c4, 0x2c7, 0x7, 0x32, 
       0x2, 0x2, 0x2c5, 0x2c8, 0x7, 0x65, 0x2, 0x2, 0x2c6, 0x2c8, 0x8, 0x21, 
       0x1, 0x2, 0x2c7, 0x2c5, 0x3, 0x2, 0x2, 0x2, 0x2c7, 0x2c6, 0x3, 0x2, 
       0x2, 0x2, 0x2c8, 0x2c9, 0x3, 0x2, 0x2, 0x2, 0x2c9, 0x2ca, 0x7, 0x3a, 
       0x2, 0x2, 0x2ca, 0x2cb, 0x8, 0x21, 0x1, 0x2, 0x2cb, 0x41, 0x3, 0x2, 
       0x2, 0x2, 0x2cc, 0x2cf, 0x7, 0x33, 0x2, 0x2, 0x2cd, 0x2d0, 0x7, 0x65, 
       0x2, 0x2, 0x2ce, 0x2d0, 0x8, 0x22, 0x1, 0x2, 0x2cf, 0x2cd, 0x3, 0x2, 
       0x2, 0x2, 0x2cf, 0x2ce, 0x3, 0x2, 0x2, 0x2, 0x2d0, 0x2d1, 0x3, 0x2, 
       0x2, 0x2, 0x2d1, 0x2d2, 0x7, 0x3a, 0x2, 0x2, 0x2d2, 0x2d3, 0x8, 0x22, 
       0x1, 0x2, 0x2d3, 0x43, 0x3, 0x2, 0x2, 0x2, 0x2d4, 0x2d7, 0x7, 0x34, 
       0x2, 0x2, 0x2d5, 0x2d8, 0x5, 0x46, 0x24, 0x2, 0x2d6, 0x2d8, 0x8, 
       0x23, 0x1, 0x2, 0x2d7, 0x2d5, 0x3, 0x2, 0x2, 0x2, 0x2d7, 0x2d6, 0x3, 
       0x2, 0x2, 0x2, 0x2d8, 0x2d9, 0x3, 0x2, 0x2, 0x2, 0x2d9, 0x2da, 0x7, 
       0x3a, 0x2, 0x2, 0x2da, 0x45, 0x3, 0x2, 0x2, 0x2, 0x2db, 0x2dd, 0x7, 
       0x70, 0x2, 0x2, 0x2dc, 0x2db, 0x3, 0x2, 0x2, 0x2, 0x2dc, 0x2dd, 0x3, 
       0x2, 0x2, 0x2, 0x2dd, 0x2de, 0x3, 0x2, 0x2, 0x2, 0x2de, 0x2e9, 0x5, 
       0x48, 0x25, 0x2, 0x2df, 0x2e1, 0x7, 0x70, 0x2, 0x2, 0x2e0, 0x2df, 
       0x3, 0x2, 0x2, 0x2, 0x2e0, 0x2e1, 0x3, 0x2, 0x2, 0x2, 0x2e1, 0x2e2, 
       0x3, 0x2, 0x2, 0x2, 0x2e2, 0x2e4, 0x7, 0x61, 0x2, 0x2, 0x2e3, 0x2e5, 
       0x7, 0x70, 0x2, 0x2, 0x2e4, 0x2e3, 0x3, 0x2, 0x2, 0x2, 0x2e4, 0x2e5, 
       0x3, 0x2, 0x2, 0x2, 0x2e5, 0x2e6, 0x3, 0x2, 0x2, 0x2, 0x2e6, 0x2e8, 
       0x5, 0x48, 0x25, 0x2, 0x2e7, 0x2e0, 0x3, 0x2, 0x2, 0x2, 0x2e8, 0x2eb, 
       0x3, 0x2, 0x2, 0x2, 0x2e9, 0x2e7, 0x3, 0x2, 0x2, 0x2, 0x2e9, 0x2ea, 
       0x3, 0x2, 0x2, 0x2, 0x2ea, 0x2ed, 0x3, 0x2, 0x2, 0x2, 0x2eb, 0x2e9, 
       0x3, 0x2, 0x2, 0x2, 0x2ec, 0x2ee, 0x7, 0x70, 0x2, 0x2, 0x2ed, 0x2ec, 
       0x3, 0x2, 0x2, 0x2, 0x2ed, 0x2ee, 0x3, 0x2, 0x2, 0x2, 0x2ee, 0x47, 
       0x3, 0x2, 0x2, 0x2, 0x2ef, 0x2f1, 0x7, 0x70, 0x2, 0x2, 0x2f0, 0x2ef, 
       0x3, 0x2, 0x2, 0x2, 0x2f0, 0x2f1, 0x3, 0x2, 0x2, 0x2, 0x2f1, 0x2f2, 
       0x3, 0x2, 0x2, 0x2, 0x2f2, 0x2fd, 0x5, 0x4a, 0x26, 0x2, 0x2f3, 0x2f5, 
       0x7, 0x70, 0x2, 0x2, 0x2f4, 0x2f3, 0x3, 0x2, 0x2, 0x2, 0x2f4, 0x2f5, 
       0x3, 0x2, 0x2, 0x2, 0x2f5, 0x2f6, 0x3, 0x2, 0x2, 0x2, 0x2f6, 0x2f8, 
       0x7, 0x5c, 0x2, 0x2, 0x2f7, 0x2f9, 0x7, 0x70, 0x2, 0x2, 0x2f8, 0x2f7, 
       0x3, 0x2, 0x2, 0x2, 0x2f8, 0x2f9, 0x3, 0x2, 0x2, 0x2, 0x2f9, 0x2fa, 
       0x3, 0x2, 0x2, 0x2, 0x2fa, 0x2fc, 0x5, 0x4a, 0x26, 0x2, 0x2fb, 0x2f4, 
       0x3, 0x2, 0x2, 0x2, 0x2fc, 0x2ff, 0x3, 0x2, 0x2, 0x2, 0x2fd, 0x2fb, 
       0x3, 0x2, 0x2, 0x2, 0x2fd, 0x2fe, 0x3, 0x2, 0x2, 0x2, 0x2fe, 0x301, 
       0x3, 0x2, 0x2, 0x2, 0x2ff, 0x2fd, 0x3, 0x2, 0x2, 0x2, 0x300, 0x302, 
       0x7, 0x70, 0x2, 0x2, 0x301, 0x300, 0x3, 0x2, 0x2, 0x2, 0x301, 0x302, 
       0x3, 0x2, 0x2, 0x2, 0x302, 0x49, 0x3, 0x2, 0x2, 0x2, 0x303, 0x305, 
       0x7, 0x70, 0x2, 0x2, 0x304, 0x303, 0x3, 0x2, 0x2, 0x2, 0x304, 0x305, 
       0x3, 0x2, 0x2, 0x2, 0x305, 0x306, 0x3, 0x2, 0x2, 0x2, 0x306, 0x308, 
       0x7, 0x35, 0x2, 0x2, 0x307, 0x309, 0x7, 0x70, 0x2, 0x2, 0x308, 0x307, 
       0x3, 0x2, 0x2, 0x2, 0x308, 0x309, 0x3, 0x2, 0x2, 0x2, 0x309, 0x30a, 
       0x3, 0x2, 0x2, 0x2, 0x30a, 0x30c, 0x5, 0x46, 0x24, 0x2, 0x30b, 0x30d, 
       0x7, 0x70, 0x2, 0x2, 0x30c, 0x30b, 0x3, 0x2, 0x2, 0x2, 0x30c, 0x30d, 
       0x3, 0x2, 0x2, 0x2, 0x30d, 0x30e, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x310, 
       0x7, 0x36, 0x2, 0x2, 0x30f, 0x311, 0x7, 0x70, 0x2, 0x2, 0x310, 0x30f, 
       0x3, 0x2, 0x2, 0x2, 0x310, 0x311, 0x3, 0x2, 0x2, 0x2, 0x311, 0x31a, 
       0x3, 0x2, 0x2, 0x2, 0x312, 0x314, 0x7, 0x70, 0x2, 0x2, 0x313, 0x312, 
       0x3, 0x2, 0x2, 0x2, 0x313, 0x314, 0x3, 0x2, 0x2, 0x2, 0x314, 0x315, 
       0x3, 0x2, 0x2, 0x2, 0x315, 0x317, 0x5, 0x4c, 0x27, 0x2, 0x316, 0x318, 
       0x7, 0x70, 0x2, 0x2, 0x317, 0x316, 0x3, 0x2, 0x2, 0x2, 0x317, 0x318, 
       0x3, 0x2, 0x2, 0x2, 0x318, 0x31a, 0x3, 0x2, 0x2, 0x2, 0x319, 0x304, 
       0x3, 0x2, 0x2, 0x2, 0x319, 0x313, 0x3, 0x2, 0x2, 0x2, 0x31a, 0x4b, 
       0x3, 0x2, 0x2, 0x2, 0x31b, 0x340, 0x5, 0x50, 0x29, 0x2, 0x31c, 0x340, 
       0x7, 0x2e, 0x2, 0x2, 0x31d, 0x31f, 0x7, 0x52, 0x2, 0x2, 0x31e, 0x31d, 
       0x3, 0x2, 0x2, 0x2, 0x31e, 0x31f, 0x3, 0x2, 0x2, 0x2, 0x31f, 0x320, 
       0x3, 0x2, 0x2, 0x2, 0x320, 0x323, 0x7, 0x65, 0x2, 0x2, 0x321, 0x322, 
       0x7, 0x62, 0x2, 0x2, 0x322, 0x324, 0x7, 0x65, 0x2, 0x2, 0x323, 0x321, 
       0x3, 0x2, 0x2, 0x2, 0x323, 0x324, 0x3, 0x2, 0x2, 0x2, 0x324, 0x33d, 
       0x3, 0x2, 0x2, 0x2, 0x325, 0x337, 0x7, 0x35, 0x2, 0x2, 0x326, 0x328, 
       0x7, 0x70, 0x2, 0x2, 0x327, 0x326, 0x3, 0x2, 0x2, 0x2, 0x327, 0x328, 
       0x3, 0x2, 0x2, 0x2, 0x328, 0x329, 0x3, 0x2, 0x2, 0x2, 0x329, 0x334, 
       0x5, 0x4e, 0x28, 0x2, 0x32a, 0x32c, 0x7, 0x70, 0x2, 0x2, 0x32b, 0x32a, 
       0x3, 0x2, 0x2, 0x2, 0x32b, 0x32c, 0x3, 0x2, 0x2, 0x2, 0x32c, 0x32d, 
       0x3, 0x2, 0x2, 0x2, 0x32d, 0x32f, 0x7, 0x5c, 0x2, 0x2, 0x32e, 0x330, 
       0x7, 0x70, 0x2, 0x2, 0x32f, 0x32e, 0x3, 0x2, 0x2, 0x2, 0x32f, 0x330, 
       0x3, 0x2, 0x2, 0x2, 0x330, 0x331, 0x3, 0x2, 0x2, 0x2, 0x331, 0x333, 
       0x5, 0x4e, 0x28, 0x2, 0x332, 0x32b, 0x3, 0x2, 0x2, 0x2, 0x333, 0x336, 
       0x3, 0x2, 0x2, 0x2, 0x334, 0x332, 0x3, 0x2, 0x2, 0x2, 0x334, 0x335, 
       0x3, 0x2, 0x2, 0x2, 0x335, 0x338, 0x3, 0x2, 0x2, 0x2, 0x336, 0x334, 
       0x3, 0x2, 0x2, 0x2, 0x337, 0x327, 0x3, 0x2, 0x2, 0x2, 0x337, 0x338, 
       0x3, 0x2, 0x2, 0x2, 0x338, 0x33a, 0x3, 0x2, 0x2, 0x2, 0x339, 0x33b, 
       0x7, 0x70, 0x2, 0x2, 0x33a, 0x339, 0x3, 0x2, 0x2, 0x2, 0x33a, 0x33b, 
       0x3, 0x2, 0x2, 0x2, 0x33b, 0x33c, 0x3, 0x2, 0x2, 0x2, 0x33c, 0x33e, 
       0x7, 0x36, 0x2, 0x2, 0x33d, 0x325, 0x3, 0x2, 0x2, 0x2, 0x33d, 0x33e, 
       0x3, 0x2, 0x2, 0x2, 0x33e, 0x340, 0x3, 0x2, 0x2, 0x2, 0x33f, 0x31b, 
       0x3, 0x2, 0x2, 0x2, 0x33f, 0x31c, 0x3, 0x2, 0x2, 0x2, 0x33f, 0x31e, 
       0x3, 0x2, 0x2, 0x2, 0x340, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x341, 0x34f, 
       0x7, 0x48, 0x2, 0x2, 0x342, 0x345, 0x7, 0x47, 0x2, 0x2, 0x343, 0x344, 
       0x7, 0x65, 0x2, 0x2, 0x344, 0x346, 0x8, 0x28, 0x1, 0x2, 0x345, 0x343, 
       0x3, 0x2, 0x2, 0x2, 0x345, 0x346, 0x3, 0x2, 0x2, 0x2, 0x346, 0x34f, 
       0x3, 0x2, 0x2, 0x2, 0x347, 0x34f, 0x7, 0x8, 0x2, 0x2, 0x348, 0x34f, 
       0x7, 0x6, 0x2, 0x2, 0x349, 0x34f, 0x7, 0x9, 0x2, 0x2, 0x34a, 0x34f, 
       0x7, 0x5, 0x2, 0x2, 0x34b, 0x34f, 0x7, 0x7, 0x2, 0x2, 0x34c, 0x34d, 
       0x7, 0x65, 0x2, 0x2, 0x34d, 0x34f, 0x8, 0x28, 0x1, 0x2, 0x34e, 0x341, 
       0x3, 0x2, 0x2, 0x2, 0x34e, 0x342, 0x3, 0x2, 0x2, 0x2, 0x34e, 0x347, 
       0x3, 0x2, 0x2, 0x2, 0x34e, 0x348, 0x3, 0x2, 0x2, 0x2, 0x34e, 0x349, 
       0x3, 0x2, 0x2, 0x2, 0x34e, 0x34a, 0x3, 0x2, 0x2, 0x2, 0x34e, 0x34b, 
       0x3, 0x2, 0x2, 0x2, 0x34e, 0x34c, 0x3, 0x2, 0x2, 0x2, 0x34f, 0x4f, 
       0x3, 0x2, 0x2, 0x2, 0x350, 0x352, 0x7, 0x2d, 0x2, 0x2, 0x351, 0x353, 
       0x7, 0x70, 0x2, 0x2, 0x352, 0x351, 0x3, 0x2, 0x2, 0x2, 0x352, 0x353, 
       0x3, 0x2, 0x2, 0x2, 0x353, 0x35d, 0x3, 0x2, 0x2, 0x2, 0x354, 0x356, 
       0x7, 0x35, 0x2, 0x2, 0x355, 0x357, 0x7, 0x70, 0x2, 0x2, 0x356, 0x355, 
       0x3, 0x2, 0x2, 0x2, 0x356, 0x357, 0x3, 0x2, 0x2, 0x2, 0x357, 0x358, 
       0x3, 0x2, 0x2, 0x2, 0x358, 0x35a, 0x7, 0x2a, 0x2, 0x2, 0x359, 0x35b, 
       0x7, 0x70, 0x2, 0x2, 0x35a, 0x359, 0x3, 0x2, 0x2, 0x2, 0x35a, 0x35b, 
       0x3, 0x2, 0x2, 0x2, 0x35b, 0x35c, 0x3, 0x2, 0x2, 0x2, 0x35c, 0x35e, 
       0x7, 0x36, 0x2, 0x2, 0x35d, 0x354, 0x3, 0x2, 0x2, 0x2, 0x35d, 0x35e, 
       0x3, 0x2, 0x2, 0x2, 0x35e, 0x360, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x361, 
       0x7, 0x70, 0x2, 0x2, 0x360, 0x35f, 0x3, 0x2, 0x2, 0x2, 0x360, 0x361, 
       0x3, 0x2, 0x2, 0x2, 0x361, 0x51, 0x3, 0x2, 0x2, 0x2, 0x362, 0x363, 
       0x7, 0xd, 0x2, 0x2, 0x363, 0x365, 0x7, 0x35, 0x2, 0x2, 0x364, 0x366, 
       0x7, 0x65, 0x2, 0x2, 0x365, 0x364, 0x3, 0x2, 0x2, 0x2, 0x365, 0x366, 
       0x3, 0x2, 0x2, 0x2, 0x366, 0x367, 0x3, 0x2, 0x2, 0x2, 0x367, 0x368, 
       0x7, 0x36, 0x2, 0x2, 0x368, 0x369, 0x7, 0x65, 0x2, 0x2, 0x369, 0x36a, 
       0x7, 0x35, 0x2, 0x2, 0x36a, 0x375, 0x8, 0x2a, 0x1, 0x2, 0x36b, 0x36c, 
       0x7, 0x65, 0x2, 0x2, 0x36c, 0x372, 0x8, 0x2a, 0x1, 0x2, 0x36d, 0x36e, 
       0x7, 0x5c, 0x2, 0x2, 0x36e, 0x36f, 0x7, 0x65, 0x2, 0x2, 0x36f, 0x371, 
       0x8, 0x2a, 0x1, 0x2, 0x370, 0x36d, 0x3, 0x2, 0x2, 0x2, 0x371, 0x374, 
       0x3, 0x2, 0x2, 0x2, 0x372, 0x370, 0x3, 0x2, 0x2, 0x2, 0x372, 0x373, 
       0x3, 0x2, 0x2, 0x2, 0x373, 0x376, 0x3, 0x2, 0x2, 0x2, 0x374, 0x372, 
       0x3, 0x2, 0x2, 0x2, 0x375, 0x36b, 0x3, 0x2, 0x2, 0x2, 0x375, 0x376, 
       0x3, 0x2, 0x2, 0x2, 0x376, 0x377, 0x3, 0x2, 0x2, 0x2, 0x377, 0x378, 
       0x7, 0x36, 0x2, 0x2, 0x378, 0x37c, 0x8, 0x2a, 0x1, 0x2, 0x379, 0x37b, 
       0x7, 0x70, 0x2, 0x2, 0x37a, 0x379, 0x3, 0x2, 0x2, 0x2, 0x37b, 0x37e, 
       0x3, 0x2, 0x2, 0x2, 0x37c, 0x37a, 0x3, 0x2, 0x2, 0x2, 0x37c, 0x37d, 
       0x3, 0x2, 0x2, 0x2, 0x37d, 0x37f, 0x3, 0x2, 0x2, 0x2, 0x37e, 0x37c, 
       0x3, 0x2, 0x2, 0x2, 0x37f, 0x383, 0x7, 0x39, 0x2, 0x2, 0x380, 0x382, 
       0x7, 0x70, 0x2, 0x2, 0x381, 0x380, 0x3, 0x2, 0x2, 0x2, 0x382, 0x385, 
       0x3, 0x2, 0x2, 0x2, 0x383, 0x381, 0x3, 0x2, 0x2, 0x2, 0x383, 0x384, 
       0x3, 0x2, 0x2, 0x2, 0x384, 0x386, 0x3, 0x2, 0x2, 0x2, 0x385, 0x383, 
       0x3, 0x2, 0x2, 0x2, 0x386, 0x38a, 0x5, 0x54, 0x2b, 0x2, 0x387, 0x389, 
       0x7, 0x70, 0x2, 0x2, 0x388, 0x387, 0x3, 0x2, 0x2, 0x2, 0x389, 0x38c, 
       0x3, 0x2, 0x2, 0x2, 0x38a, 0x388, 0x3, 0x2, 0x2, 0x2, 0x38a, 0x38b, 
       0x3, 0x2, 0x2, 0x2, 0x38b, 0x53, 0x3, 0x2, 0x2, 0x2, 0x38c, 0x38a, 
       0x3, 0x2, 0x2, 0x2, 0x38d, 0x391, 0x5, 0x56, 0x2c, 0x2, 0x38e, 0x38f, 
       0x7, 0x3a, 0x2, 0x2, 0x38f, 0x392, 0x7, 0x61, 0x2, 0x2, 0x390, 0x392, 
       0x5, 0x56, 0x2c, 0x2, 0x391, 0x38e, 0x3, 0x2, 0x2, 0x2, 0x391, 0x390, 
       0x3, 0x2, 0x2, 0x2, 0x392, 0x55, 0x3, 0x2, 0x2, 0x2, 0x393, 0x397, 
       0x7, 0x40, 0x2, 0x2, 0x394, 0x398, 0x5, 0x8c, 0x47, 0x2, 0x395, 0x398, 
       0x5, 0x8e, 0x48, 0x2, 0x396, 0x398, 0x8, 0x2c, 0x1, 0x2, 0x397, 0x394, 
       0x3, 0x2, 0x2, 0x2, 0x397, 0x395, 0x3, 0x2, 0x2, 0x2, 0x397, 0x396, 
       0x3, 0x2, 0x2, 0x2, 0x398, 0x39b, 0x3, 0x2, 0x2, 0x2, 0x399, 0x39b, 
       0x5, 0xbe, 0x60, 0x2, 0x39a, 0x393, 0x3, 0x2, 0x2, 0x2, 0x39a, 0x399, 
       0x3, 0x2, 0x2, 0x2, 0x39b, 0x57, 0x3, 0x2, 0x2, 0x2, 0x39c, 0x39d, 
       0x7, 0xe, 0x2, 0x2, 0x39d, 0x39e, 0x7, 0x35, 0x2, 0x2, 0x39e, 0x39f, 
       0x8, 0x2d, 0x1, 0x2, 0x39f, 0x3a0, 0x5, 0x66, 0x34, 0x2, 0x3a0, 0x3a7, 
       0x8, 0x2d, 0x1, 0x2, 0x3a1, 0x3a2, 0x7, 0x5c, 0x2, 0x2, 0x3a2, 0x3a3, 
       0x5, 0x66, 0x34, 0x2, 0x3a3, 0x3a4, 0x8, 0x2d, 0x1, 0x2, 0x3a4, 0x3a6, 
       0x3, 0x2, 0x2, 0x2, 0x3a5, 0x3a1, 0x3, 0x2, 0x2, 0x2, 0x3a6, 0x3a9, 
       0x3, 0x2, 0x2, 0x2, 0x3a7, 0x3a5, 0x3, 0x2, 0x2, 0x2, 0x3a7, 0x3a8, 
       0x3, 0x2, 0x2, 0x2, 0x3a8, 0x3aa, 0x3, 0x2, 0x2, 0x2, 0x3a9, 0x3a7, 
       0x3, 0x2, 0x2, 0x2, 0x3aa, 0x3ac, 0x7, 0x36, 0x2, 0x2, 0x3ab, 0x3ad, 
       0x5, 0x6c, 0x37, 0x2, 0x3ac, 0x3ab, 0x3, 0x2, 0x2, 0x2, 0x3ac, 0x3ad, 
       0x3, 0x2, 0x2, 0x2, 0x3ad, 0x3af, 0x3, 0x2, 0x2, 0x2, 0x3ae, 0x3b0, 
       0x7, 0x70, 0x2, 0x2, 0x3af, 0x3ae, 0x3, 0x2, 0x2, 0x2, 0x3b0, 0x3b1, 
       0x3, 0x2, 0x2, 0x2, 0x3b1, 0x3af, 0x3, 0x2, 0x2, 0x2, 0x3b1, 0x3b2, 
       0x3, 0x2, 0x2, 0x2, 0x3b2, 0x3b3, 0x3, 0x2, 0x2, 0x2, 0x3b3, 0x3b4, 
       0x5, 0x7e, 0x40, 0x2, 0x3b4, 0x59, 0x3, 0x2, 0x2, 0x2, 0x3b5, 0x3b6, 
       0x7, 0x14, 0x2, 0x2, 0x3b6, 0x3b7, 0x7, 0x35, 0x2, 0x2, 0x3b7, 0x3ba, 
       0x7, 0x5, 0x2, 0x2, 0x3b8, 0x3b9, 0x7, 0x5c, 0x2, 0x2, 0x3b9, 0x3bb, 
       0x7, 0x8, 0x2, 0x2, 0x3ba, 0x3b8, 0x3, 0x2, 0x2, 0x2, 0x3ba, 0x3bb, 
       0x3, 0x2, 0x2, 0x2, 0x3bb, 0x3bc, 0x3, 0x2, 0x2, 0x2, 0x3bc, 0x3bd, 
       0x7, 0x36, 0x2, 0x2, 0x3bd, 0x3be, 0x7, 0x70, 0x2, 0x2, 0x3be, 0x5b, 
       0x3, 0x2, 0x2, 0x2, 0x3bf, 0x3c0, 0x7, 0x15, 0x2, 0x2, 0x3c0, 0x3c1, 
       0x5, 0x64, 0x33, 0x2, 0x3c1, 0x3c2, 0x7, 0x70, 0x2, 0x2, 0x3c2, 0x5d, 
       0x3, 0x2, 0x2, 0x2, 0x3c3, 0x3c4, 0x7, 0x16, 0x2, 0x2, 0x3c4, 0x3c5, 
       0x5, 0x64, 0x33, 0x2, 0x3c5, 0x3c6, 0x7, 0x70, 0x2, 0x2, 0x3c6, 0x5f, 
       0x3, 0x2, 0x2, 0x2, 0x3c7, 0x3c8, 0x7, 0x17, 0x2, 0x2, 0x3c8, 0x3c9, 
       0x5, 0x64, 0x33, 0x2, 0x3c9, 0x3ca, 0x7, 0x70, 0x2, 0x2, 0x3ca, 0x61, 
       0x3, 0x2, 0x2, 0x2, 0x3cb, 0x3cc, 0x7, 0x18, 0x2, 0x2, 0x3cc, 0x3cd, 
       0x5, 0x64, 0x33, 0x2, 0x3cd, 0x3ce, 0x7, 0x70, 0x2, 0x2, 0x3ce, 0x63, 
       0x3, 0x2, 0x2, 0x2, 0x3cf, 0x3d0, 0x7, 0x35, 0x2, 0x2, 0x3d0, 0x3d1, 
       0x7, 0x65, 0x2, 0x2, 0x3d1, 0x3d7, 0x8, 0x33, 0x1, 0x2, 0x3d2, 0x3d3, 
       0x7, 0x5c, 0x2, 0x2, 0x3d3, 0x3d4, 0x7, 0x65, 0x2, 0x2, 0x3d4, 0x3d6, 
       0x8, 0x33, 0x1, 0x2, 0x3d5, 0x3d2, 0x3, 0x2, 0x2, 0x2, 0x3d6, 0x3d9, 
       0x3, 0x2, 0x2, 0x2, 0x3d7, 0x3d5, 0x3, 0x2, 0x2, 0x2, 0x3d7, 0x3d8, 
       0x3, 0x2, 0x2, 0x2, 0x3d8, 0x3da, 0x3, 0x2, 0x2, 0x2, 0x3d9, 0x3d7, 
       0x3, 0x2, 0x2, 0x2, 0x3da, 0x3db, 0x7, 0x36, 0x2, 0x2, 0x3db, 0x65, 
       0x3, 0x2, 0x2, 0x2, 0x3dc, 0x3de, 0x7, 0x4b, 0x2, 0x2, 0x3dd, 0x3dc, 
       0x3, 0x2, 0x2, 0x2, 0x3dd, 0x3de, 0x3, 0x2, 0x2, 0x2, 0x3de, 0x3df, 
       0x3, 0x2, 0x2, 0x2, 0x3df, 0x3e0, 0x5, 0x68, 0x35, 0x2, 0x3e0, 0x67, 
       0x3, 0x2, 0x2, 0x2, 0x3e1, 0x3e2, 0x6, 0x35, 0x3, 0x2, 0x3e2, 0x3e5, 
       0x7, 0x65, 0x2, 0x2, 0x3e3, 0x3e5, 0x8, 0x35, 0x1, 0x2, 0x3e4, 0x3e1, 
       0x3, 0x2, 0x2, 0x2, 0x3e4, 0x3e3, 0x3, 0x2, 0x2, 0x2, 0x3e5, 0x69, 
       0x3, 0x2, 0x2, 0x2, 0x3e6, 0x3e8, 0xa, 0x7, 0x2, 0x2, 0x3e7, 0x3e6, 
       0x3, 0x2, 0x2, 0x2, 0x3e8, 0x3e9, 0x3, 0x2, 0x2, 0x2, 0x3e9, 0x3e7, 
       0x3, 0x2, 0x2, 0x2, 0x3e9, 0x3ea, 0x3, 0x2, 0x2, 0x2, 0x3ea, 0x3f4, 
       0x3, 0x2, 0x2, 0x2, 0x3eb, 0x3ec, 0x7, 0x35, 0x2, 0x2, 0x3ec, 0x3ed, 
       0x5, 0x6a, 0x36, 0x2, 0x3ed, 0x3ee, 0x7, 0x36, 0x2, 0x2, 0x3ee, 0x3f4, 
       0x3, 0x2, 0x2, 0x2, 0x3ef, 0x3f0, 0x7, 0x37, 0x2, 0x2, 0x3f0, 0x3f1, 
       0x5, 0x6a, 0x36, 0x2, 0x3f1, 0x3f2, 0x7, 0x38, 0x2, 0x2, 0x3f2, 0x3f4, 
       0x3, 0x2, 0x2, 0x2, 0x3f3, 0x3e7, 0x3, 0x2, 0x2, 0x2, 0x3f3, 0x3eb, 
       0x3, 0x2, 0x2, 0x2, 0x3f3, 0x3ef, 0x3, 0x2, 0x2, 0x2, 0x3f4, 0x3f5, 
       0x3, 0x2, 0x2, 0x2, 0x3f5, 0x3f6, 0x5, 0x6a, 0x36, 0x2, 0x3f6, 0x6b, 
       0x3, 0x2, 0x2, 0x2, 0x3f7, 0x3fb, 0x5, 0x6e, 0x38, 0x2, 0x3f8, 0x3fb, 
       0x5, 0x70, 0x39, 0x2, 0x3f9, 0x3fb, 0x5, 0x72, 0x3a, 0x2, 0x3fa, 
       0x3f7, 0x3, 0x2, 0x2, 0x2, 0x3fa, 0x3f8, 0x3, 0x2, 0x2, 0x2, 0x3fa, 
       0x3f9, 0x3, 0x2, 0x2, 0x2, 0x3fb, 0x3fd, 0x3, 0x2, 0x2, 0x2, 0x3fc, 
       0x3fe, 0x5, 0x78, 0x3d, 0x2, 0x3fd, 0x3fc, 0x3, 0x2, 0x2, 0x2, 0x3fd, 
       0x3fe, 0x3, 0x2, 0x2, 0x2, 0x3fe, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x3ff, 
       0x400, 0x7, 0x27, 0x2, 0x2, 0x400, 0x401, 0x7, 0x35, 0x2, 0x2, 0x401, 
       0x402, 0x9, 0x8, 0x2, 0x2, 0x402, 0x403, 0x7, 0x36, 0x2, 0x2, 0x403, 
       0x6f, 0x3, 0x2, 0x2, 0x2, 0x404, 0x405, 0x7, 0x23, 0x2, 0x2, 0x405, 
       0x406, 0x7, 0x35, 0x2, 0x2, 0x406, 0x407, 0x9, 0x9, 0x2, 0x2, 0x407, 
       0x408, 0x7, 0x5c, 0x2, 0x2, 0x408, 0x409, 0x7, 0x7, 0x2, 0x2, 0x409, 
       0x40a, 0x7, 0x5c, 0x2, 0x2, 0x40a, 0x411, 0x7, 0x5, 0x2, 0x2, 0x40b, 
       0x40c, 0x7, 0x5c, 0x2, 0x2, 0x40c, 0x40f, 0x5, 0x74, 0x3b, 0x2, 0x40d, 
       0x40e, 0x7, 0x5c, 0x2, 0x2, 0x40e, 0x410, 0x5, 0x74, 0x3b, 0x2, 0x40f, 
       0x40d, 0x3, 0x2, 0x2, 0x2, 0x40f, 0x410, 0x3, 0x2, 0x2, 0x2, 0x410, 
       0x412, 0x3, 0x2, 0x2, 0x2, 0x411, 0x40b, 0x3, 0x2, 0x2, 0x2, 0x411, 
       0x412, 0x3, 0x2, 0x2, 0x2, 0x412, 0x413, 0x3, 0x2, 0x2, 0x2, 0x413, 
       0x414, 0x7, 0x36, 0x2, 0x2, 0x414, 0x71, 0x3, 0x2, 0x2, 0x2, 0x415, 
       0x416, 0x7, 0x26, 0x2, 0x2, 0x416, 0x417, 0x7, 0x35, 0x2, 0x2, 0x417, 
       0x418, 0x9, 0x9, 0x2, 0x2, 0x418, 0x419, 0x7, 0x5c, 0x2, 0x2, 0x419, 
       0x41a, 0x7, 0x5, 0x2, 0x2, 0x41a, 0x41b, 0x7, 0x36, 0x2, 0x2, 0x41b, 
       0x73, 0x3, 0x2, 0x2, 0x2, 0x41c, 0x41d, 0x7, 0x5, 0x2, 0x2, 0x41d, 
       0x41e, 0x7, 0x5c, 0x2, 0x2, 0x41e, 0x41f, 0x5, 0x76, 0x3c, 0x2, 0x41f, 
       0x75, 0x3, 0x2, 0x2, 0x2, 0x420, 0x421, 0x6, 0x3c, 0x4, 0x2, 0x421, 
       0x424, 0x7, 0x65, 0x2, 0x2, 0x422, 0x424, 0x8, 0x3c, 0x1, 0x2, 0x423, 
       0x420, 0x3, 0x2, 0x2, 0x2, 0x423, 0x422, 0x3, 0x2, 0x2, 0x2, 0x424, 
       0x77, 0x3, 0x2, 0x2, 0x2, 0x425, 0x428, 0x5, 0x7a, 0x3e, 0x2, 0x426, 
       0x428, 0x5, 0x7c, 0x3f, 0x2, 0x427, 0x425, 0x3, 0x2, 0x2, 0x2, 0x427, 
       0x426, 0x3, 0x2, 0x2, 0x2, 0x428, 0x79, 0x3, 0x2, 0x2, 0x2, 0x429, 
       0x42a, 0x7, 0x20, 0x2, 0x2, 0x42a, 0x42b, 0x7, 0x35, 0x2, 0x2, 0x42b, 
       0x42c, 0x7, 0x5, 0x2, 0x2, 0x42c, 0x42d, 0x7, 0x5c, 0x2, 0x2, 0x42d, 
       0x42e, 0x7, 0x5, 0x2, 0x2, 0x42e, 0x42f, 0x7, 0x36, 0x2, 0x2, 0x42f, 
       0x7b, 0x3, 0x2, 0x2, 0x2, 0x430, 0x431, 0x7, 0x1f, 0x2, 0x2, 0x431, 
       0x432, 0x7, 0x35, 0x2, 0x2, 0x432, 0x433, 0x5, 0x6a, 0x36, 0x2, 0x433, 
       0x434, 0x7, 0x5c, 0x2, 0x2, 0x434, 0x435, 0x5, 0x6a, 0x36, 0x2, 0x435, 
       0x436, 0x7, 0x36, 0x2, 0x2, 0x436, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x437, 
       0x439, 0x5, 0x80, 0x41, 0x2, 0x438, 0x437, 0x3, 0x2, 0x2, 0x2, 0x439, 
       0x43a, 0x3, 0x2, 0x2, 0x2, 0x43a, 0x438, 0x3, 0x2, 0x2, 0x2, 0x43a, 
       0x43b, 0x3, 0x2, 0x2, 0x2, 0x43b, 0x43c, 0x3, 0x2, 0x2, 0x2, 0x43c, 
       0x43d, 0x7, 0x65, 0x2, 0x2, 0x43d, 0x43e, 0x7, 0x35, 0x2, 0x2, 0x43e, 
       0x44a, 0x8, 0x40, 0x1, 0x2, 0x43f, 0x440, 0x5, 0x88, 0x45, 0x2, 0x440, 
       0x447, 0x8, 0x40, 0x1, 0x2, 0x441, 0x442, 0x7, 0x5c, 0x2, 0x2, 0x442, 
       0x443, 0x5, 0x88, 0x45, 0x2, 0x443, 0x444, 0x8, 0x40, 0x1, 0x2, 0x444, 
       0x446, 0x3, 0x2, 0x2, 0x2, 0x445, 0x441, 0x3, 0x2, 0x2, 0x2, 0x446, 
       0x449, 0x3, 0x2, 0x2, 0x2, 0x447, 0x445, 0x3, 0x2, 0x2, 0x2, 0x447, 
       0x448, 0x3, 0x2, 0x2, 0x2, 0x448, 0x44b, 0x3, 0x2, 0x2, 0x2, 0x449, 
       0x447, 0x3, 0x2, 0x2, 0x2, 0x44a, 0x43f, 0x3, 0x2, 0x2, 0x2, 0x44a, 
       0x44b, 0x3, 0x2, 0x2, 0x2, 0x44b, 0x44c, 0x3, 0x2, 0x2, 0x2, 0x44c, 
       0x44d, 0x7, 0x36, 0x2, 0x2, 0x44d, 0x451, 0x8, 0x40, 0x1, 0x2, 0x44e, 
       0x450, 0x7, 0x70, 0x2, 0x2, 0x44f, 0x44e, 0x3, 0x2, 0x2, 0x2, 0x450, 
       0x453, 0x3, 0x2, 0x2, 0x2, 0x451, 0x44f, 0x3, 0x2, 0x2, 0x2, 0x451, 
       0x452, 0x3, 0x2, 0x2, 0x2, 0x452, 0x454, 0x3, 0x2, 0x2, 0x2, 0x453, 
       0x451, 0x3, 0x2, 0x2, 0x2, 0x454, 0x458, 0x7, 0x39, 0x2, 0x2, 0x455, 
       0x457, 0xa, 0xa, 0x2, 0x2, 0x456, 0x455, 0x3, 0x2, 0x2, 0x2, 0x457, 
       0x45a, 0x3, 0x2, 0x2, 0x2, 0x458, 0x456, 0x3, 0x2, 0x2, 0x2, 0x458, 
       0x459, 0x3, 0x2, 0x2, 0x2, 0x459, 0x45c, 0x3, 0x2, 0x2, 0x2, 0x45a, 
       0x458, 0x3, 0x2, 0x2, 0x2, 0x45b, 0x45d, 0x7, 0x70, 0x2, 0x2, 0x45c, 
       0x45b, 0x3, 0x2, 0x2, 0x2, 0x45d, 0x45e, 0x3, 0x2, 0x2, 0x2, 0x45e, 
       0x45c, 0x3, 0x2, 0x2, 0x2, 0x45e, 0x45f, 0x3, 0x2, 0x2, 0x2, 0x45f, 
       0x7f, 0x3, 0x2, 0x2, 0x2, 0x460, 0x469, 0x5, 0x82, 0x42, 0x2, 0x461, 
       0x46a, 0x7, 0x4f, 0x2, 0x2, 0x462, 0x46a, 0x7, 0x5a, 0x2, 0x2, 0x463, 
       0x465, 0x7, 0x4b, 0x2, 0x2, 0x464, 0x463, 0x3, 0x2, 0x2, 0x2, 0x465, 
       0x468, 0x3, 0x2, 0x2, 0x2, 0x466, 0x464, 0x3, 0x2, 0x2, 0x2, 0x466, 
       0x467, 0x3, 0x2, 0x2, 0x2, 0x467, 0x46a, 0x3, 0x2, 0x2, 0x2, 0x468, 
       0x466, 0x3, 0x2, 0x2, 0x2, 0x469, 0x461, 0x3, 0x2, 0x2, 0x2, 0x469, 
       0x462, 0x3, 0x2, 0x2, 0x2, 0x469, 0x466, 0x3, 0x2, 0x2, 0x2, 0x46a, 
       0x81, 0x3, 0x2, 0x2, 0x2, 0x46b, 0x477, 0x7, 0x65, 0x2, 0x2, 0x46c, 
       0x46e, 0x7, 0x54, 0x2, 0x2, 0x46d, 0x46f, 0x5, 0x84, 0x43, 0x2, 0x46e, 
       0x46d, 0x3, 0x2, 0x2, 0x2, 0x46e, 0x46f, 0x3, 0x2, 0x2, 0x2, 0x46f, 
       0x470, 0x3, 0x2, 0x2, 0x2, 0x470, 0x478, 0x7, 0x55, 0x2, 0x2, 0x471, 
       0x473, 0x7, 0x65, 0x2, 0x2, 0x472, 0x471, 0x3, 0x2, 0x2, 0x2, 0x473, 
       0x476, 0x3, 0x2, 0x2, 0x2, 0x474, 0x472, 0x3, 0x2, 0x2, 0x2, 0x474, 
       0x475, 0x3, 0x2, 0x2, 0x2, 0x475, 0x478, 0x3, 0x2, 0x2, 0x2, 0x476, 
       0x474, 0x3, 0x2, 0x2, 0x2, 0x477, 0x46c, 0x3, 0x2, 0x2, 0x2, 0x477, 
       0x474, 0x3, 0x2, 0x2, 0x2, 0x478, 0x83, 0x3, 0x2, 0x2, 0x2, 0x479, 
       0x47e, 0x5, 0x86, 0x44, 0x2, 0x47a, 0x47b, 0x7, 0x5c, 0x2, 0x2, 0x47b, 
       0x47d, 0x5, 0x86, 0x44, 0x2, 0x47c, 0x47a, 0x3, 0x2, 0x2, 0x2, 0x47d, 
       0x480, 0x3, 0x2, 0x2, 0x2, 0x47e, 0x47c, 0x3, 0x2, 0x2, 0x2, 0x47e, 
       0x47f, 0x3, 0x2, 0x2, 0x2, 0x47f, 0x85, 0x3, 0x2, 0x2, 0x2, 0x480, 
       0x47e, 0x3, 0x2, 0x2, 0x2, 0x481, 0x484, 0x5, 0x82, 0x42, 0x2, 0x482, 
       0x484, 0x5, 0xc2, 0x62, 0x2, 0x483, 0x481, 0x3, 0x2, 0x2, 0x2, 0x483, 
       0x482, 0x3, 0x2, 0x2, 0x2, 0x484, 0x87, 0x3, 0x2, 0x2, 0x2, 0x485, 
       0x486, 0x5, 0x80, 0x41, 0x2, 0x486, 0x48a, 0x7, 0x65, 0x2, 0x2, 0x487, 
       0x489, 0x5, 0x8a, 0x46, 0x2, 0x488, 0x487, 0x3, 0x2, 0x2, 0x2, 0x489, 
       0x48c, 0x3, 0x2, 0x2, 0x2, 0x48a, 0x488, 0x3, 0x2, 0x2, 0x2, 0x48a, 
       0x48b, 0x3, 0x2, 0x2, 0x2, 0x48b, 0x89, 0x3, 0x2, 0x2, 0x2, 0x48c, 
       0x48a, 0x3, 0x2, 0x2, 0x2, 0x48d, 0x48e, 0x7, 0x37, 0x2, 0x2, 0x48e, 
       0x48f, 0x9, 0xb, 0x2, 0x2, 0x48f, 0x490, 0x7, 0x38, 0x2, 0x2, 0x490, 
       0x8b, 0x3, 0x2, 0x2, 0x2, 0x491, 0x492, 0x7, 0x25, 0x2, 0x2, 0x492, 
       0x493, 0x7, 0x41, 0x2, 0x2, 0x493, 0x494, 0x5, 0x92, 0x4a, 0x2, 0x494, 
       0x495, 0x7, 0x62, 0x2, 0x2, 0x495, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x496, 
       0x498, 0x7, 0x65, 0x2, 0x2, 0x497, 0x499, 0x5, 0x90, 0x49, 0x2, 0x498, 
       0x497, 0x3, 0x2, 0x2, 0x2, 0x498, 0x499, 0x3, 0x2, 0x2, 0x2, 0x499, 
       0x49c, 0x3, 0x2, 0x2, 0x2, 0x49a, 0x49b, 0x7, 0x41, 0x2, 0x2, 0x49b, 
       0x49d, 0x5, 0x92, 0x4a, 0x2, 0x49c, 0x49a, 0x3, 0x2, 0x2, 0x2, 0x49c, 
       0x49d, 0x3, 0x2, 0x2, 0x2, 0x49d, 0x49e, 0x3, 0x2, 0x2, 0x2, 0x49e, 
       0x49f, 0x7, 0x62, 0x2, 0x2, 0x49f, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x4a0, 
       0x4a1, 0x7, 0x35, 0x2, 0x2, 0x4a1, 0x4a6, 0x5, 0x94, 0x4b, 0x2, 0x4a2, 
       0x4a3, 0x7, 0x5c, 0x2, 0x2, 0x4a3, 0x4a5, 0x5, 0x94, 0x4b, 0x2, 0x4a4, 
       0x4a2, 0x3, 0x2, 0x2, 0x2, 0x4a5, 0x4a8, 0x3, 0x2, 0x2, 0x2, 0x4a6, 
       0x4a4, 0x3, 0x2, 0x2, 0x2, 0x4a6, 0x4a7, 0x3, 0x2, 0x2, 0x2, 0x4a7, 
       0x4a9, 0x3, 0x2, 0x2, 0x2, 0x4a8, 0x4a6, 0x3, 0x2, 0x2, 0x2, 0x4a9, 
       0x4aa, 0x7, 0x36, 0x2, 0x2, 0x4aa, 0x91, 0x3, 0x2, 0x2, 0x2, 0x4ab, 
       0x4ad, 0x7, 0x70, 0x2, 0x2, 0x4ac, 0x4ab, 0x3, 0x2, 0x2, 0x2, 0x4ad, 
       0x4b0, 0x3, 0x2, 0x2, 0x2, 0x4ae, 0x4ac, 0x3, 0x2, 0x2, 0x2, 0x4ae, 
       0x4af, 0x3, 0x2, 0x2, 0x2, 0x4af, 0x4b2, 0x3, 0x2, 0x2, 0x2, 0x4b0, 
       0x4ae, 0x3, 0x2, 0x2, 0x2, 0x4b1, 0x4b3, 0x7, 0x43, 0x2, 0x2, 0x4b2, 
       0x4b1, 0x3, 0x2, 0x2, 0x2, 0x4b2, 0x4b3, 0x3, 0x2, 0x2, 0x2, 0x4b3, 
       0x4b4, 0x3, 0x2, 0x2, 0x2, 0x4b4, 0x4b6, 0x5, 0x9a, 0x4e, 0x2, 0x4b5, 
       0x4b7, 0x5, 0x9c, 0x4f, 0x2, 0x4b6, 0x4b5, 0x3, 0x2, 0x2, 0x2, 0x4b6, 
       0x4b7, 0x3, 0x2, 0x2, 0x2, 0x4b7, 0x4ba, 0x3, 0x2, 0x2, 0x2, 0x4b8, 
       0x4b9, 0x9, 0xc, 0x2, 0x2, 0x4b9, 0x4bb, 0x5, 0x92, 0x4a, 0x2, 0x4ba, 
       0x4b8, 0x3, 0x2, 0x2, 0x2, 0x4ba, 0x4bb, 0x3, 0x2, 0x2, 0x2, 0x4bb, 
       0x93, 0x3, 0x2, 0x2, 0x2, 0x4bc, 0x4c2, 0x5, 0xc2, 0x62, 0x2, 0x4bd, 
       0x4c2, 0x7, 0x9, 0x2, 0x2, 0x4be, 0x4c2, 0x5, 0x96, 0x4c, 0x2, 0x4bf, 
       0x4c2, 0x5, 0x9a, 0x4e, 0x2, 0x4c0, 0x4c2, 0x7, 0x48, 0x2, 0x2, 0x4c1, 
       0x4bc, 0x3, 0x2, 0x2, 0x2, 0x4c1, 0x4bd, 0x3, 0x2, 0x2, 0x2, 0x4c1, 
       0x4be, 0x3, 0x2, 0x2, 0x2, 0x4c1, 0x4bf, 0x3, 0x2, 0x2, 0x2, 0x4c1, 
       0x4c0, 0x3, 0x2, 0x2, 0x2, 0x4c2, 0x95, 0x3, 0x2, 0x2, 0x2, 0x4c3, 
       0x4c9, 0x7, 0x37, 0x2, 0x2, 0x4c4, 0x4c7, 0x5, 0x98, 0x4d, 0x2, 0x4c5, 
       0x4c6, 0x7, 0x50, 0x2, 0x2, 0x4c6, 0x4c8, 0x5, 0x94, 0x4b, 0x2, 0x4c7, 
       0x4c5, 0x3, 0x2, 0x2, 0x2, 0x4c7, 0x4c8, 0x3, 0x2, 0x2, 0x2, 0x4c8, 
       0x4ca, 0x3, 0x2, 0x2, 0x2, 0x4c9, 0x4c4, 0x3, 0x2, 0x2, 0x2, 0x4c9, 
       0x4ca, 0x3, 0x2, 0x2, 0x2, 0x4ca, 0x4cb, 0x3, 0x2, 0x2, 0x2, 0x4cb, 
       0x4cc, 0x7, 0x38, 0x2, 0x2, 0x4cc, 0x97, 0x3, 0x2, 0x2, 0x2, 0x4cd, 
       0x4d0, 0x5, 0x94, 0x4b, 0x2, 0x4ce, 0x4cf, 0x7, 0x5c, 0x2, 0x2, 0x4cf, 
       0x4d1, 0x5, 0x98, 0x4d, 0x2, 0x4d0, 0x4ce, 0x3, 0x2, 0x2, 0x2, 0x4d0, 
       0x4d1, 0x3, 0x2, 0x2, 0x2, 0x4d1, 0x99, 0x3, 0x2, 0x2, 0x2, 0x4d2, 
       0x4d6, 0x7, 0x35, 0x2, 0x2, 0x4d3, 0x4d5, 0x7, 0x70, 0x2, 0x2, 0x4d4, 
       0x4d3, 0x3, 0x2, 0x2, 0x2, 0x4d5, 0x4d8, 0x3, 0x2, 0x2, 0x2, 0x4d6, 
       0x4d4, 0x3, 0x2, 0x2, 0x2, 0x4d6, 0x4d7, 0x3, 0x2, 0x2, 0x2, 0x4d7, 
       0x4d9, 0x3, 0x2, 0x2, 0x2, 0x4d8, 0x4d6, 0x3, 0x2, 0x2, 0x2, 0x4d9, 
       0x4dd, 0x5, 0x92, 0x4a, 0x2, 0x4da, 0x4dc, 0x7, 0x70, 0x2, 0x2, 0x4db, 
       0x4da, 0x3, 0x2, 0x2, 0x2, 0x4dc, 0x4df, 0x3, 0x2, 0x2, 0x2, 0x4dd, 
       0x4db, 0x3, 0x2, 0x2, 0x2, 0x4dd, 0x4de, 0x3, 0x2, 0x2, 0x2, 0x4de, 
       0x4e0, 0x3, 0x2, 0x2, 0x2, 0x4df, 0x4dd, 0x3, 0x2, 0x2, 0x2, 0x4e0, 
       0x4e4, 0x7, 0x36, 0x2, 0x2, 0x4e1, 0x4e3, 0x7, 0x70, 0x2, 0x2, 0x4e2, 
       0x4e1, 0x3, 0x2, 0x2, 0x2, 0x4e3, 0x4e6, 0x3, 0x2, 0x2, 0x2, 0x4e4, 
       0x4e2, 0x3, 0x2, 0x2, 0x2, 0x4e4, 0x4e5, 0x3, 0x2, 0x2, 0x2, 0x4e5, 
       0x4eb, 0x3, 0x2, 0x2, 0x2, 0x4e6, 0x4e4, 0x3, 0x2, 0x2, 0x2, 0x4e7, 
       0x4eb, 0x7, 0x52, 0x2, 0x2, 0x4e8, 0x4eb, 0x5, 0xb8, 0x5d, 0x2, 0x4e9, 
       0x4eb, 0x5, 0x9e, 0x50, 0x2, 0x4ea, 0x4d2, 0x3, 0x2, 0x2, 0x2, 0x4ea, 
       0x4e7, 0x3, 0x2, 0x2, 0x2, 0x4ea, 0x4e8, 0x3, 0x2, 0x2, 0x2, 0x4ea, 
       0x4e9, 0x3, 0x2, 0x2, 0x2, 0x4eb, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x4ec, 
       0x4f0, 0x7, 0x5d, 0x2, 0x2, 0x4ed, 0x4ef, 0x7, 0x70, 0x2, 0x2, 0x4ee, 
       0x4ed, 0x3, 0x2, 0x2, 0x2, 0x4ef, 0x4f2, 0x3, 0x2, 0x2, 0x2, 0x4f0, 
       0x4ee, 0x3, 0x2, 0x2, 0x2, 0x4f0, 0x4f1, 0x3, 0x2, 0x2, 0x2, 0x4f1, 
       0x4f4, 0x3, 0x2, 0x2, 0x2, 0x4f2, 0x4f0, 0x3, 0x2, 0x2, 0x2, 0x4f3, 
       0x4f5, 0x7, 0x43, 0x2, 0x2, 0x4f4, 0x4f3, 0x3, 0x2, 0x2, 0x2, 0x4f4, 
       0x4f5, 0x3, 0x2, 0x2, 0x2, 0x4f5, 0x4f6, 0x3, 0x2, 0x2, 0x2, 0x4f6, 
       0x4f7, 0x5, 0x9a, 0x4e, 0x2, 0x4f7, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x4f8, 
       0x4fb, 0x5, 0xa0, 0x51, 0x2, 0x4f9, 0x4fa, 0x7, 0x42, 0x2, 0x2, 0x4fa, 
       0x4fc, 0x5, 0xa0, 0x51, 0x2, 0x4fb, 0x4f9, 0x3, 0x2, 0x2, 0x2, 0x4fb, 
       0x4fc, 0x3, 0x2, 0x2, 0x2, 0x4fc, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x4fd, 
       0x501, 0x5, 0xa4, 0x53, 0x2, 0x4fe, 0x4ff, 0x5, 0xa2, 0x52, 0x2, 
       0x4ff, 0x500, 0x5, 0xa0, 0x51, 0x2, 0x500, 0x502, 0x3, 0x2, 0x2, 
       0x2, 0x501, 0x4fe, 0x3, 0x2, 0x2, 0x2, 0x501, 0x502, 0x3, 0x2, 0x2, 
       0x2, 0x502, 0xa1, 0x3, 0x2, 0x2, 0x2, 0x503, 0x504, 0x9, 0xd, 0x2, 
       0x2, 0x504, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x505, 0x509, 0x5, 0xa8, 0x55, 
       0x2, 0x506, 0x507, 0x5, 0xa6, 0x54, 0x2, 0x507, 0x508, 0x5, 0xa4, 
       0x53, 0x2, 0x508, 0x50a, 0x3, 0x2, 0x2, 0x2, 0x509, 0x506, 0x3, 0x2, 
       0x2, 0x2, 0x509, 0x50a, 0x3, 0x2, 0x2, 0x2, 0x50a, 0xa5, 0x3, 0x2, 
       0x2, 0x2, 0x50b, 0x50c, 0x7, 0x4b, 0x2, 0x2, 0x50c, 0x50f, 0x7, 0x4b, 
       0x2, 0x2, 0x50d, 0x50f, 0x7, 0x4e, 0x2, 0x2, 0x50e, 0x50b, 0x3, 0x2, 
       0x2, 0x2, 0x50e, 0x50d, 0x3, 0x2, 0x2, 0x2, 0x50f, 0xa7, 0x3, 0x2, 
       0x2, 0x2, 0x510, 0x514, 0x5, 0xac, 0x57, 0x2, 0x511, 0x512, 0x5, 
       0xaa, 0x56, 0x2, 0x512, 0x513, 0x5, 0xa8, 0x55, 0x2, 0x513, 0x515, 
       0x3, 0x2, 0x2, 0x2, 0x514, 0x511, 0x3, 0x2, 0x2, 0x2, 0x514, 0x515, 
       0x3, 0x2, 0x2, 0x2, 0x515, 0xa9, 0x3, 0x2, 0x2, 0x2, 0x516, 0x51f, 
       0x7, 0x4b, 0x2, 0x2, 0x517, 0x51f, 0x7, 0x2f, 0x2, 0x2, 0x518, 0x51f, 
       0x7, 0x21, 0x2, 0x2, 0x519, 0x51f, 0x7, 0x28, 0x2, 0x2, 0x51a, 0x51c, 
       0x7, 0x4c, 0x2, 0x2, 0x51b, 0x51d, 0x7, 0x4c, 0x2, 0x2, 0x51c, 0x51b, 
       0x3, 0x2, 0x2, 0x2, 0x51c, 0x51d, 0x3, 0x2, 0x2, 0x2, 0x51d, 0x51f, 
       0x3, 0x2, 0x2, 0x2, 0x51e, 0x516, 0x3, 0x2, 0x2, 0x2, 0x51e, 0x517, 
       0x3, 0x2, 0x2, 0x2, 0x51e, 0x518, 0x3, 0x2, 0x2, 0x2, 0x51e, 0x519, 
       0x3, 0x2, 0x2, 0x2, 0x51e, 0x51a, 0x3, 0x2, 0x2, 0x2, 0x51f, 0xab, 
       0x3, 0x2, 0x2, 0x2, 0x520, 0x526, 0x5, 0xb0, 0x59, 0x2, 0x521, 0x522, 
       0x5, 0xae, 0x58, 0x2, 0x522, 0x523, 0x5, 0xac, 0x57, 0x2, 0x523, 
       0x525, 0x3, 0x2, 0x2, 0x2, 0x524, 0x521, 0x3, 0x2, 0x2, 0x2, 0x525, 
       0x528, 0x3, 0x2, 0x2, 0x2, 0x526, 0x524, 0x3, 0x2, 0x2, 0x2, 0x526, 
       0x527, 0x3, 0x2, 0x2, 0x2, 0x527, 0xad, 0x3, 0x2, 0x2, 0x2, 0x528, 
       0x526, 0x3, 0x2, 0x2, 0x2, 0x529, 0x52a, 0x9, 0x4, 0x2, 0x2, 0x52a, 
       0xaf, 0x3, 0x2, 0x2, 0x2, 0x52b, 0x52d, 0x5, 0xae, 0x58, 0x2, 0x52c, 
       0x52b, 0x3, 0x2, 0x2, 0x2, 0x52c, 0x52d, 0x3, 0x2, 0x2, 0x2, 0x52d, 
       0x52e, 0x3, 0x2, 0x2, 0x2, 0x52e, 0x52f, 0x5, 0xb2, 0x5a, 0x2, 0x52f, 
       0xb1, 0x3, 0x2, 0x2, 0x2, 0x530, 0x531, 0x7, 0x35, 0x2, 0x2, 0x531, 
       0x532, 0x5, 0xa0, 0x51, 0x2, 0x532, 0x533, 0x7, 0x36, 0x2, 0x2, 0x533, 
       0x539, 0x3, 0x2, 0x2, 0x2, 0x534, 0x539, 0x5, 0xb4, 0x5b, 0x2, 0x535, 
       0x539, 0x5, 0xb6, 0x5c, 0x2, 0x536, 0x539, 0x7, 0x9, 0x2, 0x2, 0x537, 
       0x539, 0x5, 0xc2, 0x62, 0x2, 0x538, 0x530, 0x3, 0x2, 0x2, 0x2, 0x538, 
       0x534, 0x3, 0x2, 0x2, 0x2, 0x538, 0x535, 0x3, 0x2, 0x2, 0x2, 0x538, 
       0x536, 0x3, 0x2, 0x2, 0x2, 0x538, 0x537, 0x3, 0x2, 0x2, 0x2, 0x539, 
       0xb3, 0x3, 0x2, 0x2, 0x2, 0x53a, 0x547, 0x7, 0x37, 0x2, 0x2, 0x53b, 
       0x540, 0x5, 0xa0, 0x51, 0x2, 0x53c, 0x53d, 0x7, 0x5c, 0x2, 0x2, 0x53d, 
       0x53f, 0x5, 0xa0, 0x51, 0x2, 0x53e, 0x53c, 0x3, 0x2, 0x2, 0x2, 0x53f, 
       0x542, 0x3, 0x2, 0x2, 0x2, 0x540, 0x53e, 0x3, 0x2, 0x2, 0x2, 0x540, 
       0x541, 0x3, 0x2, 0x2, 0x2, 0x541, 0x545, 0x3, 0x2, 0x2, 0x2, 0x542, 
       0x540, 0x3, 0x2, 0x2, 0x2, 0x543, 0x544, 0x7, 0x50, 0x2, 0x2, 0x544, 
       0x546, 0x5, 0xa0, 0x51, 0x2, 0x545, 0x543, 0x3, 0x2, 0x2, 0x2, 0x545, 
       0x546, 0x3, 0x2, 0x2, 0x2, 0x546, 0x548, 0x3, 0x2, 0x2, 0x2, 0x547, 
       0x53b, 0x3, 0x2, 0x2, 0x2, 0x547, 0x548, 0x3, 0x2, 0x2, 0x2, 0x548, 
       0x549, 0x3, 0x2, 0x2, 0x2, 0x549, 0x54a, 0x7, 0x38, 0x2, 0x2, 0x54a, 
       0xb5, 0x3, 0x2, 0x2, 0x2, 0x54b, 0x558, 0x7, 0x65, 0x2, 0x2, 0x54c, 
       0x555, 0x7, 0x35, 0x2, 0x2, 0x54d, 0x552, 0x5, 0xa0, 0x51, 0x2, 0x54e, 
       0x54f, 0x7, 0x5c, 0x2, 0x2, 0x54f, 0x551, 0x5, 0xa0, 0x51, 0x2, 0x550, 
       0x54e, 0x3, 0x2, 0x2, 0x2, 0x551, 0x554, 0x3, 0x2, 0x2, 0x2, 0x552, 
       0x550, 0x3, 0x2, 0x2, 0x2, 0x552, 0x553, 0x3, 0x2, 0x2, 0x2, 0x553, 
       0x556, 0x3, 0x2, 0x2, 0x2, 0x554, 0x552, 0x3, 0x2, 0x2, 0x2, 0x555, 
       0x54d, 0x3, 0x2, 0x2, 0x2, 0x555, 0x556, 0x3, 0x2, 0x2, 0x2, 0x556, 
       0x557, 0x3, 0x2, 0x2, 0x2, 0x557, 0x559, 0x7, 0x36, 0x2, 0x2, 0x558, 
       0x54c, 0x3, 0x2, 0x2, 0x2, 0x558, 0x559, 0x3, 0x2, 0x2, 0x2, 0x559, 
       0xb7, 0x3, 0x2, 0x2, 0x2, 0x55a, 0x55b, 0x5, 0xbc, 0x5f, 0x2, 0x55b, 
       0x55c, 0x5, 0xba, 0x5e, 0x2, 0x55c, 0x562, 0x3, 0x2, 0x2, 0x2, 0x55d, 
       0x55f, 0x7, 0x65, 0x2, 0x2, 0x55e, 0x560, 0x5, 0xba, 0x5e, 0x2, 0x55f, 
       0x55e, 0x3, 0x2, 0x2, 0x2, 0x55f, 0x560, 0x3, 0x2, 0x2, 0x2, 0x560, 
       0x562, 0x3, 0x2, 0x2, 0x2, 0x561, 0x55a, 0x3, 0x2, 0x2, 0x2, 0x561, 
       0x55d, 0x3, 0x2, 0x2, 0x2, 0x562, 0xb9, 0x3, 0x2, 0x2, 0x2, 0x563, 
       0x567, 0x7, 0x35, 0x2, 0x2, 0x564, 0x566, 0x7, 0x70, 0x2, 0x2, 0x565, 
       0x564, 0x3, 0x2, 0x2, 0x2, 0x566, 0x569, 0x3, 0x2, 0x2, 0x2, 0x567, 
       0x565, 0x3, 0x2, 0x2, 0x2, 0x567, 0x568, 0x3, 0x2, 0x2, 0x2, 0x568, 
       0x56a, 0x3, 0x2, 0x2, 0x2, 0x569, 0x567, 0x3, 0x2, 0x2, 0x2, 0x56a, 
       0x575, 0x5, 0x94, 0x4b, 0x2, 0x56b, 0x56f, 0x7, 0x5c, 0x2, 0x2, 0x56c, 
       0x56e, 0x7, 0x70, 0x2, 0x2, 0x56d, 0x56c, 0x3, 0x2, 0x2, 0x2, 0x56e, 
       0x571, 0x3, 0x2, 0x2, 0x2, 0x56f, 0x56d, 0x3, 0x2, 0x2, 0x2, 0x56f, 
       0x570, 0x3, 0x2, 0x2, 0x2, 0x570, 0x572, 0x3, 0x2, 0x2, 0x2, 0x571, 
       0x56f, 0x3, 0x2, 0x2, 0x2, 0x572, 0x574, 0x5, 0x94, 0x4b, 0x2, 0x573, 
       0x56b, 0x3, 0x2, 0x2, 0x2, 0x574, 0x577, 0x3, 0x2, 0x2, 0x2, 0x575, 
       0x573, 0x3, 0x2, 0x2, 0x2, 0x575, 0x576, 0x3, 0x2, 0x2, 0x2, 0x576, 
       0x57b, 0x3, 0x2, 0x2, 0x2, 0x577, 0x575, 0x3, 0x2, 0x2, 0x2, 0x578, 
       0x57a, 0x7, 0x70, 0x2, 0x2, 0x579, 0x578, 0x3, 0x2, 0x2, 0x2, 0x57a, 
       0x57d, 0x3, 0x2, 0x2, 0x2, 0x57b, 0x579, 0x3, 0x2, 0x2, 0x2, 0x57b, 
       0x57c, 0x3, 0x2, 0x2, 0x2, 0x57c, 0x57e, 0x3, 0x2, 0x2, 0x2, 0x57d, 
       0x57b, 0x3, 0x2, 0x2, 0x2, 0x57e, 0x57f, 0x7, 0x36, 0x2, 0x2, 0x57f, 
       0xbb, 0x3, 0x2, 0x2, 0x2, 0x580, 0x581, 0x9, 0xe, 0x2, 0x2, 0x581, 
       0xbd, 0x3, 0x2, 0x2, 0x2, 0x582, 0x584, 0xa, 0xf, 0x2, 0x2, 0x583, 
       0x582, 0x3, 0x2, 0x2, 0x2, 0x584, 0x585, 0x3, 0x2, 0x2, 0x2, 0x585, 
       0x583, 0x3, 0x2, 0x2, 0x2, 0x585, 0x586, 0x3, 0x2, 0x2, 0x2, 0x586, 
       0xbf, 0x3, 0x2, 0x2, 0x2, 0x587, 0x58b, 0x6, 0x61, 0x5, 0x2, 0x588, 
       0x58a, 0xa, 0xa, 0x2, 0x2, 0x589, 0x588, 0x3, 0x2, 0x2, 0x2, 0x58a, 
       0x58d, 0x3, 0x2, 0x2, 0x2, 0x58b, 0x589, 0x3, 0x2, 0x2, 0x2, 0x58b, 
       0x58c, 0x3, 0x2, 0x2, 0x2, 0x58c, 0x58e, 0x3, 0x2, 0x2, 0x2, 0x58d, 
       0x58b, 0x3, 0x2, 0x2, 0x2, 0x58e, 0x58f, 0x7, 0x70, 0x2, 0x2, 0x58f, 
       0xc1, 0x3, 0x2, 0x2, 0x2, 0x590, 0x591, 0x9, 0x10, 0x2, 0x2, 0x591, 
       0xc3, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xc5, 0xcd, 0xeb, 0xf5, 0x101, 0x104, 
       0x117, 0x11c, 0x11e, 0x124, 0x12b, 0x133, 0x13b, 0x143, 0x14b, 0x15d, 
       0x160, 0x162, 0x165, 0x16a, 0x16d, 0x173, 0x176, 0x17a, 0x181, 0x185, 
       0x190, 0x19c, 0x19f, 0x1a2, 0x1ab, 0x1b2, 0x1b6, 0x1bb, 0x1bf, 0x1c3, 
       0x1c7, 0x1cc, 0x1d0, 0x1d4, 0x1d8, 0x1dd, 0x1e1, 0x1e5, 0x1e9, 0x1ee, 
       0x1f2, 0x1f6, 0x1fa, 0x1ff, 0x203, 0x210, 0x214, 0x218, 0x21c, 0x220, 
       0x223, 0x226, 0x22a, 0x22e, 0x232, 0x235, 0x238, 0x23c, 0x23f, 0x243, 
       0x247, 0x24a, 0x24e, 0x253, 0x25a, 0x25c, 0x260, 0x264, 0x26a, 0x26e, 
       0x273, 0x277, 0x27e, 0x286, 0x28b, 0x290, 0x298, 0x2a0, 0x2a2, 0x2a7, 
       0x2ab, 0x2ae, 0x2b4, 0x2c2, 0x2c7, 0x2cf, 0x2d7, 0x2dc, 0x2e0, 0x2e4, 
       0x2e9, 0x2ed, 0x2f0, 0x2f4, 0x2f8, 0x2fd, 0x301, 0x304, 0x308, 0x30c, 
       0x310, 0x313, 0x317, 0x319, 0x31e, 0x323, 0x327, 0x32b, 0x32f, 0x334, 
       0x337, 0x33a, 0x33d, 0x33f, 0x345, 0x34e, 0x352, 0x356, 0x35a, 0x35d, 
       0x360, 0x365, 0x372, 0x375, 0x37c, 0x383, 0x38a, 0x391, 0x397, 0x39a, 
       0x3a7, 0x3ac, 0x3b1, 0x3ba, 0x3d7, 0x3dd, 0x3e4, 0x3e9, 0x3f3, 0x3fa, 
       0x3fd, 0x40f, 0x411, 0x423, 0x427, 0x43a, 0x447, 0x44a, 0x451, 0x458, 
       0x45e, 0x466, 0x469, 0x46e, 0x474, 0x477, 0x47e, 0x483, 0x48a, 0x498, 
       0x49c, 0x4a6, 0x4ae, 0x4b2, 0x4b6, 0x4ba, 0x4c1, 0x4c7, 0x4c9, 0x4d0, 
       0x4d6, 0x4dd, 0x4e4, 0x4ea, 0x4f0, 0x4f4, 0x4fb, 0x501, 0x509, 0x50e, 
       0x514, 0x51c, 0x51e, 0x526, 0x52c, 0x538, 0x540, 0x545, 0x547, 0x552, 
       0x555, 0x558, 0x55f, 0x561, 0x567, 0x56f, 0x575, 0x57b, 0x585, 0x58b, 
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
