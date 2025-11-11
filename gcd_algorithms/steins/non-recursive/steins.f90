!
! iterative/non-recursive version of stein's algo.
! for finding GCD of two numbers
! see accompanying recursive version in c
! for exposition on the alogorithm
!
! since practicing fortran
! got to implement our own version of __builtin_ctzl to find trailing zeros
! 

module steins
    implicit none
contains

    ! function: gcd
    ! -------------
    ! find the Greatest Common Divisor
    ! using Stein's binary approach to Euclid's alogrithm
    ! non-recusively
    ! translated the algo. as found here:
    ! https://cp-algorithms.com/algebra/euclid-algorithm.html
    !
    function gcd(x,y) result(r)
        implicit none
        integer(kind = 8)  :: x, y
        integer(kind = 8)  :: r
        integer(kind = 8) :: k

        if (x.eq.0) then
            r = y
            return
        endif

        if (y.eq.0) then
            r = x
            return
        endif

        ! get the smallest k (power of two)
        k = ctz(OR(x,y))

        ! remove even factors from x
        x = SHIFTR(x, ctz(x))

        do while(y.gt.0)
            y = SHIFTR(y, ctz(y))

            if (x.gt.y) then
                ! swap so x is always smaller
                call swap(x,y)
            endif

            ! difference of largest minus smallest
            y = y - x
        enddo
        ! add back the power of 2
        r = SHIFTL(x, k)
        return

    end function gcd
    
    ! function: ctz
    ! -------------
    ! Count Trailing Zeros
    ! using GCC's bit test function BTEST
    ! since no in-built CTZ like in C
    !
    function ctz(x) result(r)
        implicit none
        integer(kind=8), intent(in) :: x
        integer(kind=8) :: r
        integer :: i                            ! counter

        if (x.eq.0) then
            r = 64      ! word size for kind = 8
            return
        endif

        do i=0,63
            if (BTEST(x,i)) then
                ! BTEST(x,i) returns logical .TRUE.
                ! if the bit at i in x is set (= 1)
                r = i
                return
            endif
        enddo
    end function ctz

    ! subroutine: swap
    ! ----------------
    ! simply swap two values
    !
    subroutine swap(x, y)
        implicit none
        integer(kind=8), intent(inout) :: x, y
        integer(kind=8) :: t                    ! temp/placeholder

        t = x
        x = y
        y = t

    end subroutine swap

end module steins

program main
    use steins
    implicit none
    integer(kind=8) :: a, b, d

    ! TODO
    ! read stdin
    ! pass value pair to gcd
    ! but now, just

    a = 192
    b = 270
    d = gcd(a, b)

    ! print result
    print *, d

end program main
