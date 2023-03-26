#ifndef __META_H__
#define __META_H__

#def_pattern metaCleanup => meta_info(gid(), 'Content', '') {
  @begin
    \#\(
    ([^\.\#]+\.[^\)])*([^\.\#]+\.\))
    \\n(*PRUNE)
  @end
};

#def_pattern metaIntroduce => meta_info(gid(), 'Header', //HEAD/@Value) {
  @begin
    \#introduce\s*\(((.{1,255})->{HEAD}\))?=>{Predicates.BAL($,')')}\s*\\n
  @end
  (\#\(([^\.\#]+\.[^\)])*([^\.\#]+\.\)\\n))*?
  \#stop\s*\\n
};

#def_pattern metaStop => meta_info(gid(), 'Footer', //HEAD/@Value) {
  \#introduce\s*\(((.{1,255})->{HEAD}\))?=>{Predicates.BAL($,')')}\s*\\n
  (\#\(([^\.\#]+\.[^\)])*([^\.\#]+\.\)\\n))*?
  @begin
    \#stop\s*\\n
  @end
};

#def_module() meta_info(GID, TYPE, HEAD) {
@goal:-brackets_off.
@goal:-asserta(meta_info(GID,TYPE,HEAD)).
};

#endif
