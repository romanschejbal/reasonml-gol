type cellT =
  | Dead
  | Live;

let createGrid = (width, height) => Array.make_matrix(height, width, Dead);

let gridMap = (fn, grid) =>
  Array.mapi(
    (yi, row) => Array.mapi((xi, cell) => fn((yi, xi), cell), row),
    grid
  );

let randomizeGrid = (chance, grid, ~seed=?) => {
  switch seed {
  | None => ()
  | Some(seed) => Random.init(seed)
  };
  gridMap(
    ((yi, xi), cell) => {
      let n = Random.float(1.);
      n >= chance ? Live : Dead;
    },
    grid
  );
};

let getCell = ((yi, xi), grid) =>
  if (yi < 0
      || yi >= Array.length(grid)
      || xi < 0
      || xi >= Array.length(grid[0])) {
    Dead;
  } else {
    grid[yi][xi];
  };

let countNeighbours = ((yi, xi), grid) =>
  List.fold_left(
    (total, (diffY, diffX)) => {
      let y = yi + diffY;
      let x = xi + diffX;
      let cell = getCell((y, x), grid);
      switch cell {
      | Dead => total
      | Live => total + 1
      };
    },
    0,
    [
      ((-1), (-1)),
      ((-1), 0),
      ((-1), 1),
      (0, (-1)),
      (0, 1),
      (1, (-1)),
      (1, 0),
      (1, 1)
    ]
  );

let iterate = grid =>
  gridMap(
    (coords, cell) => {
      let neighboursCount = countNeighbours(coords, grid);
      switch neighboursCount {
      | 0
      | 1
      | 2 => Dead
      | _ => cell
      };
    },
    grid
  );