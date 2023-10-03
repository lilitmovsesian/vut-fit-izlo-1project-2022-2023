#include <stddef.h>
#include "cnf.h"

// Projekt vypracovala
// Movsesian Lilit
// xmovse00


void example_condition(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    for (unsigned subject_i = 0; subject_i < num_of_subjects; ++subject_i) {
        for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {
            // vytvori novou klauzuli
            Clause *example_clause = create_new_clause(num_of_subjects, num_of_semesters);
            // vlozi do klauzule literal x_{i,j}
            add_literal_to_clause(example_clause, true, subject_i, semester_j);
            // vlozi do klauzule literal ~x_{i,j}
            add_literal_to_clause(example_clause, false, subject_i, semester_j);
            // prida klauzuli do formule
            add_clause_to_formula(example_clause, formula);
        }
    }
}

/*Tato funkce generuje klauzuli pro kazdy predmet takovou, ze predmet 1 je bud zapsan do 1 semesru, nebo do 
druheho/treriho/ctvrteno atd (xp1s1 nebo xp1s2 nebo xp1s3)*/
void each_subject_enrolled_at_least_once(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);
    for (unsigned subject_i = 0; subject_i < num_of_subjects; ++subject_i) {
	Clause* clause = create_new_clause(num_of_subjects, num_of_semesters);
	for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {
		add_literal_to_clause (clause, true, subject_i, semester_j);
	}
	add_clause_to_formula(clause, formula);
    }
}

/*Tato funkce generuje vetsi pocet klauzuli pomoci cyklu ve kterych pro kazdy predmet beru kazdy mozny par 
 semestru a generuji klauzuli ve formatu (-xp1s1 nebo -xp1s2) ^ (-xp1s1 nebo -xp1s3) atd*/
void each_subject_enrolled_at_most_once(CNF *formula, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    for (unsigned subject_i = 0; subject_i < num_of_subjects; ++subject_i) {
	for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {
		for (unsigned semester_l = semester_j+1; semester_l < num_of_semesters; semester_l++) {
                	Clause* clause = create_new_clause(num_of_subjects, num_of_semesters);
                	add_literal_to_clause (clause, false, subject_i, semester_j);
                	add_literal_to_clause (clause, false, subject_i, semester_l);
                	add_clause_to_formula(clause, formula);
                }
	}
    }
}


/* V teto funkci prochazim cyklem kazdy prerekvizitni radek, a generuji klauzuli pro kazdy prerekvizitni 
 radek a pro kazdy mozny semester prvniho predmetu, ze bud drivejsi predmet nebyl zapsan v drivejsim 
 semestru, nebo je zapsan pozdejdsi predmet v jednom ze zbylych pozdejsim semestrech*/ 
void add_prerequisities_to_formula(CNF *formula, Prerequisity* prerequisities, unsigned num_of_prerequisities, unsigned num_of_subjects, unsigned num_of_semesters) {
    assert(formula != NULL);
    assert(prerequisities != NULL);
    assert(num_of_subjects > 0);
    assert(num_of_semesters > 0);

    for (unsigned i = 0; i < num_of_prerequisities; ++i) {
    
    	for (unsigned semester_j = 0; semester_j < num_of_semesters; ++semester_j) {
  
    		Clause* clause = create_new_clause(num_of_subjects, num_of_semesters);
  		add_literal_to_clause (clause, false, prerequisities[i].earlier_subject, semester_j);
    		for (unsigned semester_l = semester_j+1; semester_l < num_of_semesters; ++semester_l) {
    			add_literal_to_clause (clause, true, prerequisities[i].later_subject, semester_l);
    		}
    		add_clause_to_formula(clause, formula);
    	}
    }
}


















