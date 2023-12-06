#define ROTATE_SPEED     0.1
#define TRANS_SPEED     0.1


  Pause  500                /* Zawieszenie na 1 sek. */
  Rotate Podstawa OX ROTATE_SPEED 40
  Rotate Podstawa.Ramie1 OX ROTATE_SPEED 40
  Rotate Podstawa.Ramie1.Ramie2 OX ROTATE_SPEED 40
  Pause  500                /* Zawieszenie na 1 sek. */
  Rotate Podstawa.Ramie1.Ramie2 OZ ROTATE_SPEED 40
  Pause  500                /* Zawieszenie na 1 sek. */
  Move Podstawa TRANS_SPEED 0.5


