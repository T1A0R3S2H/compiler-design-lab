#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 10
#define MAX_SYMBOLS 20
#define MAX_STATE 50

// Define terminal and non-terminal symbols
typedef enum {
    T_EOF, T_ID, T_PLUS, T_STAR, T_LPAREN, T_RPAREN, T_NUM, T_INVALID
} Terminal;

typedef enum {
    NT_EXPR, NT_TERM, NT_FACTOR, NT_INVALID_RULE
} NonTerminal;

// Define a structure for grammar rules
typedef struct {
    NonTerminal lhs; // Left-hand side non-terminal
    Terminal rhs[MAX_SYMBOLS]; // Right-hand side terminals/non-terminals
    int rhs_len; // Length of the right-hand side
} Rule;

// Define a structure for items in the LR(0) items
typedef struct {
    Rule rule;
    int dot_pos; // Position of the dot in the production
} Item;

// Define a structure for states (a collection of items)
typedef struct {
    Item items[MAX_RULES];
    int item_count;
} State;

// Declare global variables for grammar rules and parsing
Rule grammar[MAX_RULES];
int grammar_count = 0;

// Function declarations
void generateCanonicalListItems(State states[], int* state_count);
void closure(State* state);
State goTo(State* state, int symbol);
void generateParsingTable(State states[], int state_count, int parse_table[MAX_STATE][MAX_SYMBOLS]);
int parse(Terminal input[], int input_size, int parse_table[MAX_STATE][MAX_SYMBOLS], State states[], int state_count);

// Grammar rules
void initGrammar() {
    grammar[grammar_count++] = (Rule){NT_EXPR, {T_ID, T_PLUS, NT_TERM}, 3}; // E -> E+T
    grammar[grammar_count++] = (Rule){NT_EXPR, {NT_TERM}, 1}; // E -> T
    grammar[grammar_count++] = (Rule){NT_TERM, {T_ID}, 1}; // T -> id
    grammar[grammar_count++] = (Rule){NT_TERM, {T_LPAREN, NT_EXPR, T_RPAREN}, 3}; // T -> (E)
    grammar[grammar_count++] = (Rule){NT_FACTOR, {T_ID}, 1}; // F -> id
    grammar[grammar_count++] = (Rule){NT_FACTOR, {T_LPAREN, NT_EXPR, T_RPAREN}, 3}; // F -> (E)
}

// Function to generate closure for a given state
void closure(State* state) {
    int i = 0;
    while (i < state->item_count) {
        Item item = state->items[i];
        if (item.rule.rhs[item.dot_pos] < T_EOF) { // If dot is before a non-terminal
            NonTerminal next_nt = item.rule.rhs[item.dot_pos];
            for (int j = 0; j < grammar_count; j++) {
                if (grammar[j].lhs == next_nt) { // Add all rules for the non-terminal
                    Item new_item = {grammar[j], 0};
                    state->items[state->item_count++] = new_item;
                }
            }
        }
        i++;
    }
}

// Function to generate the canonical item list
void generateCanonicalListItems(State states[], int* state_count) {
    State initial_state = {0};
    initial_state.items[0] = (Item){grammar[0], 0}; // Start from the first rule
    initial_state.item_count = 1;
    closure(&initial_state);

    states[(*state_count)++] = initial_state;

    int i = 0;
    while (i < *state_count) {
        State current_state = states[i];
        for (int symbol = T_EOF + 1; symbol < T_INVALID; symbol++) {
            State next_state = goTo(&current_state, symbol);
            if (next_state.item_count > 0) {
                // Check if the state already exists
                int found = 0;
                for (int j = 0; j < *state_count; j++) {
                    if (memcmp(&states[j], &next_state, sizeof(State)) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    states[(*state_count)++] = next_state;
                }
            }
        }
        i++;
    }
}

// Function to simulate the GOTO operation
State goTo(State* state, int symbol) {
    State next_state = {0};
    for (int i = 0; i < state->item_count; i++) {
        Item item = state->items[i];
        if (item.rule.rhs[item.dot_pos] == symbol) {
            Item new_item = item;
            new_item.dot_pos++;
            next_state.items[next_state.item_count++] = new_item;
        }
    }
    closure(&next_state);
    return next_state;
}

// Function to generate the parsing table
void generateParsingTable(State states[], int state_count, int parse_table[MAX_STATE][MAX_SYMBOLS]) {
    for (int i = 0; i < state_count; i++) {
        for (int j = 0; j < states[i].item_count; j++) {
            Item item = states[i].items[j];
            if (item.dot_pos < item.rule.rhs_len) {
                int symbol = item.rule.rhs[item.dot_pos];
                if (symbol < T_EOF) { // Terminal symbols
                    parse_table[i][symbol] = item.rule.lhs;
                }
            }
        }
    }
}

// Function to parse an input string
int parse(Terminal input[], int input_size, int parse_table[MAX_STATE][MAX_SYMBOLS], State states[], int state_count) {
    int stack[MAX_STATE];
    int top = -1;
    stack[++top] = 0; // Start state

    int idx = 0;
    while (idx < input_size) {
        int state = stack[top];
        Terminal symbol = input[idx];

        if (parse_table[state][symbol] != -1) {
            // Shift or reduce
            int action = parse_table[state][symbol];
            if (action == 0) { // Shift action
                stack[++top] = symbol;
                idx++;
            } else { // Reduce action
                // Apply the reduction rule
                Rule rule = grammar[action];
                for (int i = 0; i < rule.rhs_len; i++) {
                    top--;
                }
                stack[++top] = rule.lhs;
            }
        } else {
            printf("Syntax error\n");
            return 0; // Error
        }
    }
    return 1; // Successful parse
}

// Main driver function with test cases
int main() {
    // Initialize grammar rules
    initGrammar();

    // Define the input strings to test
    Terminal input1[] = {T_ID, T_PLUS, T_ID, T_EOF};  // Example: id + id
    Terminal input2[] = {T_LPAREN, T_ID, T_PLUS, T_ID, T_RPAREN, T_EOF};  // Example: (id + id)
    Terminal input3[] = {T_ID, T_EOF};  // Example: id
    Terminal input4[] = {T_LPAREN, T_ID, T_RPAREN, T_EOF};  // Example: (id)
    Terminal input5[] = {T_PLUS, T_ID, T_EOF};  // Invalid example: +id

    int input_sizes[] = {sizeof(input1) / sizeof(input1[0]), 
                         sizeof(input2) / sizeof(input2[0]), 
                         sizeof(input3) / sizeof(input3[0]), 
                         sizeof(input4) / sizeof(input4[0]), 
                         sizeof(input5) / sizeof(input5[0])};

    // Generate canonical item list (states)
    State states[MAX_STATE];
    int state_count = 0;
    generateCanonicalListItems(states, &state_count);

    // Generate the parsing table
    int parse_table[MAX_STATE][MAX_SYMBOLS] = {0};
    generateParsingTable(states, state_count, parse_table);

    // Test each input string
    for (int i = 0; i < 5; i++) {
        Terminal* input = NULL;
        int input_size = input_sizes[i];

        switch (i) {
            case 0: input = input1; break;
            case 1: input = input2; break;
            case 2: input = input3; break;
            case 3: input = input4; break;
            case 4: input = input5; break;
        }

        printf("Testing input %d: ", i + 1);

        // Parse the input string
        if (parse(input, input_size, parse_table, states, state_count)) {
            printf("Input is accepted.\n");
        } else {
            printf("Input is rejected.\n");
        }
    }

    return 0;
}
