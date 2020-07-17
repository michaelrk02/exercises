// Skadoosh!!! There's actually nothing here =D

// But don't worry. You can find the implementation here:
//  https://github.com/michaelrk02/tlx-toki-course-cp/blob/master/01-pengenalan-pemrograman-kompetitif/C.cpp

// Alright, the idea is to create an automata with |Q| equals to |P|+2 where Q represents a finite set of states and P is the pattern string containing wildcards.
// Now why is there a +2? Okay, I'll explain this here.
// The 0th state (Q0) is the 'trap' state where a string obviously mismatches the pattern. It redirects back to itself when receiving any character.
// Then, Q1 is the initial state where it begins.
// If the automata receives a character that matches the first character of the pattern, it will jump to state Q2. Otherwise, Q0.
// Q2..Qn describe the states those correspond to their own character in a pattern.
//
// For example: suppose a pattern P = foo*bar
// Then Q1 will redirect to Q2 when it receives letter 'f'. Otherwise fallback (in this case, to Q0, that is, an initial fallback state).
// Q2 will redirect to Q3 when it receives letter 'o', and so on until it reaches the final state (Qn a.k.a. last character in a pattern)
//
// When the automata encounters an asterisk, it will set its fallback state to Qa where 'a' represents a state corresponds to the asterisk character in a pattern.
// But that's not enough. We also need to redirect Q(a-1) and Q(a) when they receive the next character in the pattern (after the asterisk symbol, in this case, b) to Q(a+1).
// Why Q(a-1) also? Because that will handle an empty wildcard too :)
// Then we need to redirect Qi..Qj (i = a+1, and Qj is the last consecutive state that does NOT contain an asterisk in its corresponding pattern) when they encounter the character after the asterisk to Q(a+1). This is useful in case the string immediately matches the pattern after a set of unknown chatacters.
// But there's one more thing. What if the pattern contains *aaa (i.e. a set of C consecutive characters, in this case C=3 and the character is 'a')?
// The solution to deal with that problem is actually simple. Just redirect Qx to its own state when receiving the same character, where x=a+C

// WAS A MAJOR BREAKTHROUGH IN MY LIFE BRUH
