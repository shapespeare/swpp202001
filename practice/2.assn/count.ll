define i32 @count_even(i32* %arr, i32 %N){
  ; Count the number of evens from
  ; %arr[0 … %N - 1]
  ; precond: 0 <= N <= 20

  entry:
    %zero.exception = icmp sgt i32 %N, 0
    br i1 %zero.exception, label %for.body, label %for.end

  for.body:
    %count = phi i32 [ 0, %entry ], [ %count.next, %for.body ]
    %ans = phi i32 [ 0, %entry ], [ %ans.next, %for.body ]
    %array.id = getelementptr inbounds i32, i32* %arr, i32 %count
    %0 = load i32, i32* %array.id
    %1 = and i32 %0, 1
    %2 = xor i32 %1, 1
    %ans.next = add i32 %2, %ans
    %count.next = add i32 %count, 1
    %exitcond = icmp eq i32 %count.next, %N
    br i1 %exitcond, label %for.end, label %for.body

  for.end:
    %ans.final = phi i32 [ 0, %entry ], [ %ans.next, %for.body ]
    ret i32 %ans.final
}
