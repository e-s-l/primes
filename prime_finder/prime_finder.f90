program prime_finder
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !
    ! Find all primes less than a given number
    !
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    use utilities ! import module for desired prime finder method & tests

    implicit none

    integer, allocatable, dimension(:) :: primes    ! array of primes
    integer :: i                                    ! counter
    logical :: tests, answ                          ! do we test?
    integer, parameter :: i32 = selected_int_kind(32)
    integer(kind = i32) :: limit                      ! limit is upper limit
    integer(kind = i32) :: found                    ! found is how many

    !!!!!!!!!!!!!
    limit = 1000000000
    ! for limit = 10**9, found = 
    ! NOTE: 
    ! compilier freaks out at 10**10 for eratostheneses v2
    ! atkins seive sigsegv (memory) for 10**9, sometimes
    !!!!!!!!!!!!!
    ! adapt so limit is user input
    ! print *, "To what upper limit shall we count the primes?"
    ! read (*, *) limit
    ! print *, limit, "? OK."
    !!!!!!!!!!!!!

    !call eratostheneses_sieve(limit, found)
    ! NOTE: this version does NOT return an array of primes
    ! so the test below cannot be implemeneted.

    !
    call atkins_sieve_v1(limit, found)

    !!!
    ! NOTE: formatting assumes numbers less than 10**13
    write(*,*) '!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'
    write(*, fmt="(1x,a,i12,a,i12,a)") "Found: ", found, " primes under ", limit, '.'
    write(*,*) '!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'
    !!!

    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!    
    !!!!!!!!
    ! tests
    !!!!!!!!
    tests = .false.
    if (tests) then
        do i=1,found
        !    print *, primes(i)
            call is_prime(primes(i), answ)
        !    print *, answ
            if (.not.answ) then 
                print *, 'shit'
            end if
        end do
    end if
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

end program prime_finder
