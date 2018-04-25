open Jest;

open Expect;

open GameOfLife;

describe("Game of lyfe", () => {
  test("createGrid of 2", () =>
    createGrid(2, 3)
    |> expect
    |> toEqual([|[|Dead, Dead|], [|Dead, Dead|], [|Dead, Dead|]|])
  );
  test("randomizeGrid with seed 1", () =>
    [|[|Dead, Dead|], [|Dead, Dead|]|]
    |> (grid => randomizeGrid(0.3, grid, ~seed=3))
    |> expect
    |> toEqual([|[|Dead, Live|], [|Dead, Dead|]|])
  );
  test("countNeighbours", () =>
    [|[|Live, Dead|], [|Dead, Dead|], [|Dead, Live|]|]
    |> countNeighbours((1, 0))
    |> expect
    |> toEqual(2)
  );
  test("two cells die", () =>
    [|[|Live, Live|]|] |> iterate |> expect |> toEqual([|[|Dead, Dead|]|])
  );
});