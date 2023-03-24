void remap_linkages(Linkage, const int *remap);
void compute_chosen_words(Sentence, Linkage, Parse_Options);

void partial_init_linkage(Linkage, unsigned int N_words);
void check_link_size(Linkage);
void remove_empty_words(Linkage);
void free_linkage(Linkage);
