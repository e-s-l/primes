program factorise
    implicit none

    !
    !!! TODO
    ! comments
    !

    integer, parameter :: big_int = selected_int_kind(38) ! 18 decimal digits
    integer, parameter :: MAX_FACTORS = 1024

    character(len=32) :: arg                              ! cmd line input
    integer(big_int) :: n                                 ! the number
    integer(big_int), dimension(MAX_FACTORS) :: factors   ! array of factors
    integer :: c                                          ! count of factors
    integer(big_int) :: cur, pow, i                       ! for the print out

    factors = 1
    c = 1

    ! get number from command line
    call get_command_argument(1, arg)
    read(arg, *) n

    ! check if number is composite
    if (is_prime(n) .eqv. .true.) then
        call exit(1)
    end if

    ! factorise
    call find_factors(n, factors, c)
    call sort_array(factors, c)

    ! print
    if (c > 0) then
        cur = factors(1)
        pow = 1
        do i = 1,c
            if (factors(i) .eq. cur) then
                pow = pow + 1
            else 
                if (cur.ne.1) then
                    write(*,'(I0,"^",I0,1X)', advance='no') cur, pow
                end if
                cur = factors(i)
                pow = 1
            end if
        end do
        if (cur.ne.1)  write(*,'(I0,"^",I0,1X)') cur, pow
    end if

    contains

    recursive subroutine find_factors(n, factors, count)
        implicit none

        integer(big_int), intent(in) :: n
        integer(big_int), dimension(MAX_FACTORS), intent(inout) :: factors
        integer, intent(inout) :: count
        integer(big_int) :: f1, f2

        if (is_prime(n) .eqv. .true.) then
            if (count < MAX_FACTORS) then
                factors(count) = n
                count = count + 1
            end if
        else
            if (MODULO(n,2) == 0) then
                call halve(n, f1, f2)
            else
                call fermat(n, f1, f2)
            end if

            call find_factors(f1, factors, count)
            call find_factors(f2, factors, count)

        end if

    end subroutine find_factors

    subroutine halve(n, f1, f2)
        implicit none
        integer(big_int), intent(in) :: n
        integer(big_int), intent(out) :: f1, f2

        f1 = 2
        f2 = n / 2

    end subroutine

    subroutine fermat(n ,f1, f2)
        implicit none
        integer(big_int), intent(in) :: n
        integer(big_int), intent(out) :: f1, f2
        integer(big_int) :: a, b, b2

        a = CEILING(SQRT(n*1.0))
        b2 = a*a - n
        b = FLOOR(SQRT(b2*1.0))

        do while (b*b .ne. b2)
            a = a + 1
            b2 = a*a - n
            b = FLOOR(SQRT(b2*1.0))
        end do

        f1 = a - b
        f2 = a + b

    end subroutine fermat

    subroutine sort_array(factors, count)
        implicit none
        integer(big_int), dimension(MAX_FACTORS), intent(inout) :: factors
        integer, intent(in) :: count
        integer(big_int) :: i, j, tmp

        do i = 1,(count-1)
            do j = (i+1), count
                if (factors(j) < factors(i)) then
                        tmp = factors(i)
                        factors(i) = factors(j)
                        factors(j) = tmp
                end if
            end do
        end do
    end subroutine sort_array

    ! no longer used...
    ! thought there might be a kind of qsort for fortran...
    integer(big_int) function comp(c1, c2)
        integer(big_int) c1, c2

        if (c1.lt.c2) comp = -1
        if (c1.eq.c2) comp = 0
        if (c1.gt.c2) comp = 1
        return

    end function

    function is_prime(x) result(p)
        implicit none

        integer(big_int) :: x, d
        logical :: p

        if (x .le. 1) then
            p = .false.
        else if (x .eq. 2) then
            p = .true.
        else if (MODULO(x,2) == 0) then
            p = .false.
        else
            p = (trial_division(x) .eq. x)
        end if

    end function is_prime

    function trial_division(x) result(d)
        implicit none
        integer(big_int) :: x, d, i

        if (x .le. 1) then
            d = 1
        else if (MODULO(x,2) == 0) then
            d = 2
        else
            d = x
            i = 3
            do while (i*i .le. x)
                if (MODULO(x,i) == 0) then
                    d = i
                    exit
                end if
                i = i + 2
            end do
        end if

    end function trial_division

end program factorise
