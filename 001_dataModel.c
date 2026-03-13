/*
    Data Model (https://en.cppreference.com/w/c/language/arithmetic_types.html)

    LP32:   Win16           - 4 Bytes Long and Pointer
    ILP32:  Win32, Unix     - 4 Bytes Long, Int and Pointer
    LLP64:  Win64           - 8 Bytes Long Long and Pointer
    LP64:   Unix            - 8 Bytes Long and Pointer

    Type specifier          Equivalent type                         Width in bits by data model 
                                                            C standard	    LP32	ILP32	LLP64	LP64

    char                    char                            at least 8	    8	    8	    8	    8
    signed char             signed char                     at least 8	    8	    8	    8	    8
    unsigned char           unsigned char                   at least 8	    8	    8	    8	    8

    short                   short int	                    at least 16	    16	    16	    16	    16
    short int               short int                       at least 16	    16	    16	    16	    16
    signed short            short int                       at least 16	    16	    16	    16	    16
    signed short int        short int                       at least 16	    16	    16	    16	    16

    unsigned short          unsigned short int              at least 16	    16	    16	    16	    16
    unsigned short int      unsigned short int              at least 16	    16	    16	    16	    16
    
    int                     int                             at least 16	    16  	32  	32  	32  
    signed                  int                             at least 16	    16  	32  	32  	32
    signed int              int                             at least 16	    16  	32  	32  	32
    
    unsigned                unsigned int                    at least 16	    16  	32  	32  	32
    unsigned int            unsigned int                    at least 16	    16  	32  	32  	32

    long                    long int	                    at least 32 	32  	32  	32  	64
    long int                long int	                    at least 32 	32  	32  	32  	64
    signed long             long int	                    at least 32 	32  	32  	32  	64
    signed long int         long int	                    at least 32 	32  	32  	32  	64

    unsigned long           unsigned long int               at least 32 	32  	32  	32  	64
    unsigned long int       unsigned long int               at least 32 	32  	32  	32  	64

    long long               long long int (C99)	            at least 64 	64  	64  	64  	64
    long long int           long long int (C99)	            at least 64 	64  	64  	64  	64
    signed long long        long long int (C99)	            at least 64 	64  	64  	64  	64
    signed long long int    long long int (C99)	            at least 64 	64  	64  	64  	64
    
    unsigned long long      unsigned long long int (C99)    at least 64 	64  	64  	64  	64
    unsigned long long int  unsigned long long int (C99)    at least 64 	64  	64  	64  	64
*/