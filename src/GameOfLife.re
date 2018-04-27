type cellT =
  | Dead
  | Live;

let createGrid = (width, height) => Array.make_matrix(height, width, Dead);

let gridMap = (fn, grid) =>
  Array.mapi(
    (yi, row) => Array.mapi((xi, cell) => fn((yi, xi), cell), row),
    grid
  );

let randomizeGrid = (~seed=?, chance, grid) => {
  switch seed {
  | None => ()
  | Some(seed) => Random.init(seed)
  };
  gridMap(
    (_, _) => {
      let n = Random.float(1.);
      n >= chance ? Dead : Live;
    },
    grid
  );
};

let getCell = ((yi, xi), grid) =>
  switch (yi, xi) {
  | _ when yi < 0 || yi >= Array.length(grid) => Dead
  | _ when xi < 0 || xi >= Array.length(grid[0]) => Dead
  | _ => grid[yi][xi]
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
      | 1 => Dead
      | 2 => cell
      | 3 => Live
      | _ => Dead
      };
    },
    grid
  );