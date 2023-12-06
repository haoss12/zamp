#define ROTATE_SPEED     0.01
#define TRANS_SPEED     0.0001

Begin_Parallel_Actions
  Pause  1000                /* Zawieszenie na 1 sek. */
End_Parallel_Actions

Begin_Parallel_Actions
  Rotate Podstawa OX ROTATE_SPEED 40
  Rotate Podstawa.Ramie1 OX ROTATE_SPEED 40
  Rotate Podstawa.Ramie1.Ramie2 OX ROTATE_SPEED 40
End_Parallel_Actions

Begin_Parallel_Actions
  Pause  1000                /* Zawieszenie na 1 sek. */
End_Parallel_Actions

Begin_Parallel_Actions
  Move Podstawa TRANS_SPEED 1
  Rotate Podstawa OY ROTATE_SPEED 50
End_Parallel_Actions

