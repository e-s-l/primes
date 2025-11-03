module utilities
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    !
    ! Classical prime finding algorithms
    !
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    contains 

    subroutine eratostheneses_sieve(limit, found)
        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        ! Classical O(log(log(n))) algorithm
        ! INPUT:
        ! limit: an arbitrary number 
        ! OUTPUT:
        ! found: the number of primes less than limit
        ! primes: an array of the found primes  
        ! INTERNAL: 
        ! mask: an array of logicals representing whether prime or not
        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        implicit none

        integer, parameter :: i32 = selected_int_kind(32)
        integer :: i, j                 ! counters   
        integer(kind = i32), intent(in) :: limit ! the upper number
        integer(kind = i32), intent(out) :: found   ! total found
        logical, dimension(limit) :: mask ! is prime boolan mask

        ! set the array of bools to the total number
        mask = .true.           ! and make it true!
        mask(1) = .false.       ! except of course


        ! the seive
        do i = 2, limit
            if (i.lt.INT(SQRT(REAL(limit)))) then
                if (mask(i)) then
                    j = i**2
                    do while (j <= limit)
                        mask(j) = .false.
                        j = j + i
                    enddo
                endif
            endif
             if (mask(i)) then
                write(*, fmt="(1x,i12,a)", advance="no") i, ','
                ! NOTE: formatting assumes numbers less than 10**13
            endif
        enddo 
      
        write(*,*)                  ! formatting...

        ! total number of positives in the mask
        found = COUNT(mask)

    end subroutine eratostheneses_sieve

    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    subroutine eratostheneses_sieve_v1(limit, found, primes)
        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        ! Classical O(log(log(n))) algorithm
        ! INPUT:
        ! limit: an arbitrary number 
        ! OUTPUT:
        ! found: the number of primes less than limit
        ! primes: an array of the found primes  
        ! INTERNAL: 
        ! mask: an array of logicals representing whether prime or not
        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        implicit none

        integer :: i, j                 ! counters
        integer, intent(in) :: limit      ! the upper number
        integer, intent(out) :: found   ! total fonud
        integer, intent(inout), allocatable, dimension(:) :: primes
                                        ! the array of primes
        integer :: msqr                 ! probably unnecessary
        logical, dimension(limit) :: mask ! is prime boolan mask

        ! set the array of bools to the total number
        mask = .true.           ! and make it true!
        mask(1) = .false.       ! except of course

        ! get the floored square root
        msqr = INT(SQRT(REAL(limit)))

        ! the seive, paralleled
        !!$OMP PARALLEL DO PRIVATE(j)
        do i = 2, msqr
            if (mask(i)) then
                j = i**2
                do while (j <= limit)
                    mask(j) = .false.
                    j = j + i
                enddo
            endif
        enddo
        !!$OMP END PARALLEL DO

        ! total number of positives in the mask
        found = COUNT(mask)
        allocate(primes(found))             ! finally
        ! prime array is index of true mask elements:
        j = 0
        do i = 1, limit
            if (mask(i)) then
                j = j + 1
                primes(j) = i
            end if
        end do

    end subroutine eratostheneses_sieve_v1

    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    subroutine is_prime(num, ans)
        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        ! a quick & dirty test for the above
        ! INPUT:
        ! num: we want to know if this is prime.
        ! OUTPUT: 
        ! ans: yes or no.
        !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        implicit none

        integer, intent(in) :: num      ! the question
        logical, intent(out) :: ans     ! the answer
        integer :: i                    ! a counter

        if (num < 2) then
            ans = .false.           ! all numbers less than two are not prime
        else if (num == 2) then
            ans = .true.
        else 
            do i = 2,(INT(SQRT(REAL(num)))) 
                if (MODULO(num,i).eq.0) then
                    ans = .false.
                    exit
                else 
                    ans = .true.
                end if
            end do
        end if

    end subroutine is_prime


    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    subroutine atkins_sieve_v1(limit, found)
        !!!!!!!!!!!!!!!!!!!!!!!!!
        ! a O(n) sieve method... 
        ! let's see
        !!!!!!!!!!!!!!!!!!!!!!!!!

        implicit none
           
        integer, parameter :: i32 = selected_int_kind(32)
        integer(kind = i32), intent(in) :: limit ! the upper number
        integer(kind = i32), intent(out) :: found   ! total found
        logical, allocatable, dimension(:) :: mask       ! is prime boolan mask
        integer(kind = i32) :: x2, y2, n, i, j, msqrt           ! counters etc.

    !    integer, parameter :: i64 = selected_int_kind(18)
    !    integer(kind=i64) :: limit, x2, y2, n, i, j, sqrt_limit, prime_count
    !    logical, allocatable :: sieve(:)

        allocate(mask(0:limit))
        mask = .false.

        msqrt = int(sqrt(real(limit)))

        do i = 1, msqrt
            x2 = i * i
            do j = 1, msqrt
                y2 = j * j

                !
                n = 4 * x2 + y2
                if (n.le.limit.and.(mod(n, 12).eq.1.or.mod(n, 12).eq.5)) then
                    mask(n) = .not.mask(n)
                end if

                ! 
                n = 3 * x2 + y2
                if (n.le.limit.and.(mod(n, 12).eq.7)) then
                    mask(n) = .not. mask(n)
                end if

                !
                if (i.gt.j) then
                    n = 3 * x2 - y2
                    if (n.le.limit.and.(mod(n, 12).eq.11)) then
                        mask(n) = .not. mask(n)
                    end if
                end if
            end do
        end do


        do i = 5, msqrt
            if (mask(i)) then
                n = i * i
                do j = n, limit, n
                    mask(j) = .false.
                end do
            end if
        end do
    
        mask(2:3) = .true.

    !    do i = 2, limit
    !     if (mask(i)) then
    !            write(*, fmt="(1x,i12,a)", advance="no") i, ','
    !            ! NOTE: formatting assumes numbers less than 10**13
    !        endif
    !    end do
    !    write(*,*)                  ! formatting...
        ! total number of positives in the mask
        found = COUNT(mask)

        deallocate(mask)

    end subroutine atkins_sieve_v1

end module utilities
