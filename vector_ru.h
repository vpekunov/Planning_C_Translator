#ifndef __VECTOR_RU__
#define __VECTOR_RU__

#include "meta.h"

#scan(vecProgram,vecScalar,vecVector,vecMat,vecInput,vecOut,vecTest,vecTerminator,metaCleanup,metaIntroduce,metaStop)

#def_xpath Mp1ii($i0,$i1) {
	(count(//Link[Name/text()="Mp" and Left/Value/text()=$i0 and Right/Value/text()=$i1]) > 0)
}

#def_xpath MVIv1ii($i0,$i1) {
	(count(//Link[Name/text()="MVIv" and Left/Value/text()=$i0 and Right/Value/text()=$i1]) > 0)
}

#def_xpath MVv1ii($i0,$i1) {
	(count(//Link[Name/text()="MVv" and Left/Value/text()=$i0 and Right/Value/text()=$i1]) > 0)
}

#def_xpath MVv1io($i0,&$o1) {
	(count(//Link[Name/text()="MVv" and Left/Value/text()=$i0 and set($o1,Right/Value/text())]) > 0)
}

#def_xpath MVv1oi(&$o0,$i1) {
	(count(//Link[Name/text()="MVv" and set($o0,Left/Value/text()) and Right/Value/text()=$i1]) > 0)
}

#def_xpath NXv0io($i0,&$o1) {
	(count(//Link[Name/text()="NXv" and Right/Value/text()=$i0 and set($o1,Left/Value/text())]) > 0)
}

#def_pattern vecProgram => vector_sentence(gid(), 'Program', '', '', '') {
  @begin
   \#\(
   ()->{V0}
   (([^\.]+\.)->{Grammar.ru{SENTENCE}})?=>{
      xpathf(SENTENCE,'MVv1oi',$V0,'программу','true'),(similar(V0,'Написать',2);similar(V0,'Составить',2))
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecScalar => vector_sentence(gid(), 'Scalar', '', '', //P0/@Value) {
  @begin
   \#\(
   ()->{V0}
   (([^\w\.]+(\w+)->{P0}[^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      xpathf(SENTENCE,'MVv1oi',$V0,'скаляр','true'),(similar(V0,'Ввести',2);similar(V0,'Определить',2))
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecVector => vector_sentence(gid(), 'Vector', '', //P1/@Value, //P0/@Value) {
  @begin
   \#\(
   (([^\w\.]+(\w+)->{P0}[^\w\.]+(\w+)->{P1}[^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      xpathf(SENTENCE,'MVv1ii','Введем','вектор','true'),
      xpathf(SENTENCE,'Mp1ii','вектор','из','true')
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecMat => vector_sentence(gid(), 'Mat', //P0/@Value, //VRES0/@Value, //P1/@Value) {
  @begin
   \#\(
   ()->{V0}()->{V3}()->{VRES0}
   (([^\w\.]+(\w+)->{P0}[^\w\.]+(\w+)->{P1}[^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      xpathf(SENTENCE,'MVv1oi',$V0,'результат','true'),
      (similar(V0,'Найдем',2);similar(V0,'Определим',2)),
      xpathf(SENTENCE,'NXv0io','результат',$V3,'true'),
      (similar(V3,'максимум',1),set($VRES0,'Max');
       similar(V3,'минимум',1),set($VRES0,'Min'))
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecInput => vector_sentence(gid(), 'Input', '', '', //P0/@Value) {
  @begin
   \#\(
   ()->{V0}
   (([^\w\.]+(\w+)->{P0}[^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      xpathf(SENTENCE,'MVv1oi',$V0,'вектор','true'),(similar(V0,'Введем',2);similar(V0,'Зададим',2)),
      xpathf(SENTENCE,'Mp1ii','вектор','с','true')
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecOut => vector_sentence(gid(), 'Out', '', '', //P0/@Value) {
  @begin
   \#\(
   ()->{V1}
   (([^\w\.]+(\w+)->{P0}[^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      xpathf(SENTENCE,'MVv1io','Вывести',$V1,'true'),(similar(V1,'вектор',2);similar(V1,'скаляр',2))
   }(*PRUNE)
   \)\\n
  @end
};

#def_pattern vecTest => vector_sentence(gid(), 'Test', //P0/@Value, '', //P1/@Value) {
  @begin
    \#\(
    (([^\x22\x27\.]+[\x22\x27]([^\x22\x27]+)->{P0}[\x22\x27][^\x22\x27\.]+[\x22\x27]([^\x22\x27]+)->{P1}[\x22\x27][^\.]*\.)->{Grammar.ru{SENTENCE}})?=>{
      xpathf(SENTENCE,'MVIv1ii','Тест','дает','true')
    }(*PRUNE)
    \)\\n
  @end
};

#def_pattern vecTerminator => vector_generate(gid()) {
  @begin
    ($)->{END}
  @end
};

#def_module() vector_sentence(GID, TYPE, HEAD, OBJECT, OP, SUBJECT) {
@goal:-brackets_off.
@goal:-asserta(vector_fact(GID,TYPE,HEAD,OBJECT,OP,SUBJECT)).
};

#def_module() vector_generate(GID) {
@goal:-brackets_off.
@goal:-true.
};

#endif
