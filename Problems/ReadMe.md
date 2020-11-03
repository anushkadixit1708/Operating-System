# Some problems based on the concepts in OS

# Cat and Mice Problem
    You are asked to design andimplement a solution to a synchronizationproblem using
    the synchronization primitives available in the OS: semaphores, locks, and con-dition
    variables. You are free to use whichever synchronization primitives you choose. The
    synchronizationproblem is called the “cats and mice” problem.
    
    The Cats and Mice Problem
    A number of cats and mice inhabit a house. The cats and mice have worked out a deal
    where the micecan steal pieces of the cats’ food, so long as the cats never see the mice
    actually doing so. If the cats see themice, then the cats must eat the mice (or else lose face
    with all of their cat friends). There are NumBowls catfood dishes,NumCats cats, and NumMice
    mice.Your job is to synchronize the cats and mice so that the following requirements are
    satisfied:
    No mouse should ever get eaten.You should assume that if a cat is eating at a food dish, any
    mouse attempting to eat from that dishor any other food dish will be seen and eaten. When
    cats aren’teating, they will not see mice eating.In other words, this requirement states that if
    a cat is eating from any bowl, then no mouse should beeating from any bowl.Only one mouse
    or one cat may eat from a given dish at any one time.Neither cats nor mice should starve.A cat or
    mouse that wants to eat should eventually be able to eat. For example, a
    synchronizationsolution that permanently prevents all mice from eating would be
    unacceptable. When we actuallytest your solution, each simulated cat and mouse will only
    eat a finite number of times; however, evenif the simulation were allowed to run forever,
    neither cats nor mice should starve.Your solution must not rely on knowledge of the numbers
    of cats and mice in the system. In particular,you should not make direct or indirect use of
    the variablesNumCatsandNumMicein your solution. (Thoseparameters should be used only
    by thecatmouse()function to create the correct numbers of cats and miceto run a particular
    test.) It is OK to make use of theNumBowlsparameter in your solution.There are many ways
    to synchronize the cats and mice that willsatisfy the requirements above. Fromamong the
    possible solutions that satisfy the requirements, weprefersolutions that are (a) efficient
    and(b) fair.An efficient solution avoids allowing food bowls to go unused when there are
    creatures waiting to eat.Sometimes it is necessary to make creatures wait, even when there
    are unused food bowls, in order to satisfythe synchronization requirements, so an efficient
    solution should avoid unnecessary delays. For example, asolution that uses a single lock to
    ensure that only one creature eats at a time (regardless of the number ofbowls) satisfies the
    problem requirements, but it is not efficient because it may delay creatures unnecessarily.To
    see this, consider a scenario in which there are 5 cats, 5 bowls and no mice. In that scenario,
    the 5 catsshould should be able to eat simultaneously.Fairness means avoiding favouring
    some creatures over others, and in particular avoiding bias againstcats or mice. For
    example, a solution that makes all mice waituntil all cats have finished eating as manytimes
    as they want satisfies the three problem requirements,but it is biased in favour of the
    cats.There is a tradeoff between efficiency and fairness. For example, consider a situation
    in which there aretwo bowls, a cat is eating at one of the bowls, and a mouse is waiting to
    eat so that it does not get seen bythe cat that is eating. Now, suppose that a second cat
    shows up, wanting to eat. Should you allow it to eatimmediately from the unused bowl? Or
    should you make it wait until the mouse has had a chance to eat?
    After all, the mouse was there first. If your solution allows the cat to eat, it has sacrificed
    some fairness for efficiency by allowing the cat to jump in front of the waiting mouse. On the
    other hand, if your solutionmakes the second cat wait then it sacrifices some efficiency since
    a bowl is left unused though there is aneligible cat waiting.Both approaches are reasonable
    (provided that there is no possibility that the waiting mouse will starve),but one leans in
    favour of performance, the other in favour offairness. You should be aware of such
    tradeoffsin your design, as we will ask you to explain them

# LRU Scheduling
    Whenever the Linux kernel needs to allocate frames of physical memory for something, it has to
    come from somewhere. If the machine was just booted, it will have lots of unused memory lying
    around, ready to be claimed. However, unused memory is wasted memory, so Linux does its best to
    fill a large percentage of memory as soon as possible. Therefore, it doesn't take long before a request
    for memory cannot be satisfied from the pool of unused frames. When this happens, a frame that is
    in use must be freed, possibly by swapping out a page that is currently held in a frame. There is also
    a kernel process, called kswapd, that frees page frames asynchronously. This is necessary because
    some kernel code has to allocate frames without the possibility of old pages being swapped out.
    The default Linux memory management employs two LRU lists: the active and inactive lists.
    Frames in both lists are managed by the second-chance LRU approximation algorithm. Frames
    evicted from the active list go to the inactive list. Frames evicted from the inactive list are freed
    (their contents are pushed out of the memory). Frames in the inactive list may also be promoted into
    the active list in certain circumstances.
    you are asked to replace the second-chance LRU approximation algorithm in both the active and
    inactive lists with a counter-based clock algorithm:
    1. Keep a reference counter for each frame, which is set at 0 initially.
    2. When try_to_free_pages() is called, you scan a frame in the following way. First,
    you add the reference bit value to the frame reference counter (and clear the reference bit at
    the same time). Then you check the reference counter. If the counter is 0, you evict the page.
    Otherwise, you decrement the counter by 1 and move the frame to the back of list (as the
    original second-chance LRU approximation normally does).
    3. Action #2 (above) alone will result in a replacement algorithm equivalent to the original
    second-chance LRU approximation. To effectively utilize the reference counter, you need
    additional counter maintenance at other occasions. To this end, you should scan the frames
    periodically (e.g., as part of the timer interrupt) and add the reference bit value to the frame
    reference counter (and clear the reference bit at the same time).
    4. Note that the reference counter may overflow. If the reference counter is already at its
    maximum value, keep it unchanged when adding the reference bit to it.
    Note that we only ask that you replace the existing LRU approximation algorithm in each list with a
    new one. You can leave the basic Linux two-list memory management in place. Also, you do not
    need to make any changes to how Linux handles dirty page eviction. If a frame to be freed contains
    a dirty page, it will have to be swapped out, but this shouldn't affect your decision on which frame
    to free. 

# Disk Scheduling
    Write a c program to demonstrate the working of the following
    disk scheduling algorithms.
    a) SCAN
    b) CSCAN
    Reference queue sequence : 2,
    3,100,10,56,3,20,100,130,60,34,80,23,10,20,180
    Total cylinders 0-199. Current position of the armhead is
    30. Compare the performance of the algorithms. Show the
    results in the form of a table.
