// Generated by BUCKLESCRIPT VERSION 3.0.0, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var Reprocessing = require("Reprocessing/src/Reprocessing.js");
var Reprocessing_Env = require("Reprocessing/src/Reprocessing_Env.js");
var Reprocessing_Draw = require("Reprocessing/src/Reprocessing_Draw.js");
var Reprocessing_Utils = require("Reprocessing/src/Reprocessing_Utils.js");
var Reprocessing_Constants = require("Reprocessing/src/Reprocessing_Constants.js");
var GameOfLife$ReasonGameOfLife = require("./GameOfLife.bs.js");

var boardSizeWidth = 60;

var boardSizeHeight = 60;

var cellSizeWidth = Caml_int32.div(600, boardSizeWidth);

var cellSizeHeight = Caml_int32.div(600, boardSizeHeight);

function setup(env) {
  Reprocessing_Env.size(600, 600, env);
  var grid = GameOfLife$ReasonGameOfLife.randomizeGrid(/* None */0, 0.5, GameOfLife$ReasonGameOfLife.createGrid(boardSizeWidth, boardSizeHeight));
  return /* record */[
          /* grid */grid,
          /* time */0
        ];
}

function draw(state, env) {
  Reprocessing_Draw.background(Reprocessing_Constants.black, env);
  var grid = state[/* grid */0];
  $$Array.iteri((function (yi, row) {
          return $$Array.iteri((function (xi, cell) {
                        Reprocessing_Draw.fill(Reprocessing_Utils.color(255, Caml_int32.imul(Caml_int32.div(255, boardSizeHeight), xi), Caml_int32.imul(Caml_int32.div(255, boardSizeWidth), yi), Reprocessing_Utils.lerp(0, 255, 1)), env);
                        if (cell === /* Live */1) {
                          return Reprocessing_Draw.rect(/* tuple */[
                                      Caml_int32.imul(xi, cellSizeWidth) + 0 | 0,
                                      Caml_int32.imul(yi, cellSizeHeight) + 0 | 0
                                    ], cellSizeWidth - 1 | 0, cellSizeHeight - 1 | 0, env);
                        } else {
                          return 0;
                        }
                      }), row);
        }), grid);
  var grid$1 = Reprocessing_Env.keyPressed(/* R */42, env) || Reprocessing_Env.keyPressed(/* Space */4, env) ? GameOfLife$ReasonGameOfLife.randomizeGrid(/* None */0, 0.5, GameOfLife$ReasonGameOfLife.createGrid(boardSizeWidth, boardSizeHeight)) : grid;
  var newTime = Reprocessing_Env.deltaTime(env) + state[/* time */1];
  var match = newTime > 0.2;
  var match$1 = newTime > 0.2;
  return /* record */[
          /* grid */match ? GameOfLife$ReasonGameOfLife.iterate(grid$1) : grid$1,
          /* time */match$1 ? 0 : newTime
        ];
}

Reprocessing.run(setup, /* None */0, /* Some */[draw], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* () */0);

var canvasSizeWidth = 600;

var canvasSizeHeight = 600;

var cellPadding = 1;

var interval = 0.2;

var chanceOfSpawningALiveCell = 0.5;

exports.canvasSizeWidth = canvasSizeWidth;
exports.canvasSizeHeight = canvasSizeHeight;
exports.boardSizeWidth = boardSizeWidth;
exports.boardSizeHeight = boardSizeHeight;
exports.cellSizeWidth = cellSizeWidth;
exports.cellSizeHeight = cellSizeHeight;
exports.cellPadding = cellPadding;
exports.interval = interval;
exports.chanceOfSpawningALiveCell = chanceOfSpawningALiveCell;
exports.setup = setup;
exports.draw = draw;
/* cellSizeWidth Not a pure module */
