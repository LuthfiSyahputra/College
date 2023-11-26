 13| (234ms) [SUCCESS] {main/func() :23} test yo
 13| (234ms) [  ...  ]   => test yo
 13| (234ms) [  ...  ]       => test yo
 13| (234ms) [  ...  ]       => test yo
 13| (234ms) [  ...  ]       => test yo
 13| (234ms) [  ...  ]       => test yo

# LOG 

## STANDARD LOG FORMAT

> Standard
 nLog | (Execution Time) [Test State]

> Main Log
 nLog | (Execution Time) [Test State] {Location} "Message"

> Child Process Log
 nLog | (Exec Time) [Test State]  Level Space {Location} message

> Misc. Process Message
 nLog | (Exec Time)             => message

> Normal Log Write
 nLog| Message


# DATA STORAGE

## STATIC DATA

> array
|  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |

> memory allocation
start_ptr |               block of memory                  | end_ptr

## DYNAMIC DATA

> Memory Allocation (static index)

| ptr_1 | ptr_2 | ptr_3 | ptr_4 | ... | ptr_n |

ptr_1 -> |               block of memory                  |
ptr_2 -> |               block of memory                  |
ptr_3 -> |               block of memory                  |
ptr_4 -> |               block of memory                  |

special_ptr -> NULL (to divide every section)

> Memory Allocation (Dynamic Index)
|               sizeof n-ptr            | NULL |

ptr_1 -> |               block of memory                  |
ptr_2 -> |               block of memory                  |
ptr_3 -> |               block of memory                  |
ptr_4 -> |               block of memory                  |

> Linked List

| start |                ...               | end
  Data  | nextptr -> data | nextptr -> ... | NULL



# RGB COLOUR

> 32-bit  | r (8-bit) | g (8-bit) | b (8-bit) |  padding (8-bit)  |

> 0x**bbggrr (32-bit datatype)

## Function Calling Convention

By struct Datatype [rgb32]
> int func((rgb32) {r, g, b});

By 32-bit integer constant [__rgb32 | rgb32u]
> int func((rgb32u) 0x00bbggrr);

By Union (pseudo-polymorphism) [rgb32_t]
> int func((rgb32_t) (rgb32) {r, g, b});
> int func((rgb32_t) (rgb32u) 0x00bbggrr);

Due to how rgb32_t union defined, you can ignore the (rgb32) struct type casting
> int func((rgb32_t) {r, g, b});



# END