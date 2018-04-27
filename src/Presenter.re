open Reprocessing;

open GameOfLife;

let canvasSizeWidth = 600;

let canvasSizeHeight = 600;

let boardSizeWidth = canvasSizeWidth / 10;

let boardSizeHeight = canvasSizeHeight / 10;

let cellSizeWidth = canvasSizeWidth / boardSizeWidth;

let cellSizeHeight = canvasSizeHeight / boardSizeHeight;

let cellPadding = 1;

let interval = 0.2;

let chanceOfSpawningALiveCell = 0.5;

type stateT = {
  grid: array(array(cellT)),
  time: float
};

let setup = env => {
  Env.size(~width=canvasSizeWidth, ~height=canvasSizeHeight, env);
  let grid =
    createGrid(boardSizeWidth, boardSizeHeight)
    |> randomizeGrid(chanceOfSpawningALiveCell);
  {grid, time: 0.};
};

let draw = (state, env) => {
  Draw.background(Constants.black, env);
  let {grid} = state;
  Array.iteri(
    (yi, row) =>
      Array.iteri(
        (xi, cell) => {
          Draw.fill(
            Utils.color(
              ~r=255,
              ~g=255 / boardSizeHeight * xi,
              ~b=255 / boardSizeWidth * yi,
              ~a=Utils.lerp(~low=0, ~high=255, ~value=1.)
            ),
            env
          );
          if (cell == Live) {
            Draw.rect(
              ~pos=(
                xi * cellSizeWidth + cellPadding / 2,
                yi * cellSizeHeight + cellPadding / 2
              ),
              ~width=cellSizeWidth - cellPadding,
              ~height=cellSizeHeight - cellPadding,
              env
            );
          };
        },
        row
      ),
    grid
  )
  |> ignore;
  let grid =
    if (Env.keyPressed(R, env) || Env.keyPressed(Space, env)) {
      createGrid(boardSizeWidth, boardSizeHeight)
      |> randomizeGrid(chanceOfSpawningALiveCell);
    } else {
      grid;
    };
  let newTime = Env.deltaTime(env) +. state.time;
  {
    time: newTime > interval ? 0. : newTime,
    grid: newTime > interval ? iterate(grid) : grid
  };
};

run(~setup, ~draw, ());