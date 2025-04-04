
        // check repeated element
        for (int m = 0; m < elements - 1; m++) {
            for (int n = m + 1; n < elements; n++) {
                if (temp[m] == temp[n]) invalid = 1;
            }
        }
        // calculate total seqs
        if (!invalid) totalSeq++;
        // check repeated row
        for (int j = 0; j < row; j++) {
            if (isEqualArray(sequence[j], temp, elements)) invalid = 1;
        }