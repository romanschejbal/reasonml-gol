open Reprocessing;

let setup = env => Env.size(~width=200, ~height=200, env);

let draw = (_state, env) => {
  Draw.background(Constants.black, env);
  Draw.fill(Constants.red, env);
  Draw.rect(~pos=(50, 50), ~width=100, ~height=100, env);
};

run(~setup, ~draw, ());