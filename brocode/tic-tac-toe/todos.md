# Todos

## Enhancements

### Scalability

While grid_dir_size is defined dynamically, many functions (e.g., checkIsSpaceFree, playerMove, etc.) still assume a 3x3 grid. You could generalize these functions to handle grids of any size.
Example: Replace hardcoded 3 in checkIsSpaceFree with tic_tac_toe_manager->grid_dir_size.

### Memory Efficiency

The use of fixed-size arrays (e.g., moves[3][3]) limits scalability. Consider dynamically allocating the board using malloc based on grid_dir_size.

### Game Play Enhancements

Add a replay option or allow players to switch roles without restarting the program.
Display instructions for selecting positions (e.g., "Enter a number between 1 and 9").

### Improved Input Validation

Ensure the player's input is strictly numeric and falls within valid bounds. Currently, entering non-numeric input could cause issues.

```c
void playerMove(tic_tac_toe_manager_t *tic_tac_toe_manager)
{
    int selected_pos = -1;
    char input[10]; // Buffer for input to handle invalid cases.

    while (true)
    {
        printf("Please select a position (1-%d) from the available free spaces: \n", tic_tac_toe_manager->movements_total);
        
        // Read input as a string
        if (!fgets(input, sizeof(input), stdin))
        {
            printf("Error reading input. Please try again.\n");
            continue;
        }

        // Check if input is numeric
        char *endptr;
        selected_pos = strtol(input, &endptr, 10);

        if (endptr == input || *endptr != '\n') // Input isn't a valid number
        {
            printf("Invalid input! Please enter a valid number.\n");
            continue;
        }

        // Validate range
        if (selected_pos < 1 || selected_pos > tic_tac_toe_manager->movements_total)
        {
            printf("Invalid position! Please enter a number between 1 and %d.\n", tic_tac_toe_manager->movements_total);
            continue;
        }

        // Adjust to zero-based index for internal representation
        selected_pos--;

        // Check if the selected position is free
        if (!checkIsSpaceFree(tic_tac_toe_manager->moves, selected_pos))
        {
            printf("Position already occupied! Please choose a different position.\n");
            continue;
        }

        // Make the move
        int row = selected_pos / tic_tac_toe_manager->row_size;
        int column = selected_pos % tic_tac_toe_manager->column_size;
        tic_tac_toe_manager->moves[row][column] = tic_tac_toe_manager->player_move_type;
        tic_tac_toe_manager->movements_available--;
        break;
    }
}
```
