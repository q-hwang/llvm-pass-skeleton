; ModuleID = 'foo.c'
source_filename = "foo.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.13.0"

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1

; Function Attrs: noinline nounwind ssp uwtable
define i32 @main(i32, i8**) #0 !prof !30 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  %8 = load i8**, i8*** %5, align 8
  %9 = getelementptr inbounds i8*, i8** %8, i64 1
  %10 = load i8*, i8** %9, align 8
  %11 = call i32 @atoi(i8* %10)
  store i32 %11, i32* %6, align 4
  store i32 0, i32* %7, align 4
  %12 = load i32, i32* %6, align 4
  %13 = icmp sgt i32 %12, 5
  br i1 %13, label %14, label %15, !prof !31

14:                                               ; preds = %2
  store i32 4, i32* %7, align 4
  br label %16

15:                                               ; preds = %2
  store i32 6, i32* %7, align 4
  br label %16

16:                                               ; preds = %15, %14
  %17 = load i32, i32* %7, align 4
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i64 0, i64 0), i32 %17)
  %19 = load i32, i32* %3, align 4
  ret i32 %19
}

declare i32 @atoi(i8*) #1

declare i32 @printf(i8*, ...) #1

attributes #0 = { noinline nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !27, !28}
!llvm.ident = !{!29}

!0 = !{i32 1, !"ProfileSummary", !1}
!1 = !{!2, !3, !4, !5, !6, !7, !8, !9}
!2 = !{!"ProfileFormat", !"InstrProf"}
!3 = !{!"TotalCount", i64 7}
!4 = !{!"MaxCount", i64 6}
!5 = !{!"MaxInternalCount", i64 1}
!6 = !{!"MaxFunctionCount", i64 6}
!7 = !{!"NumCounts", i64 2}
!8 = !{!"NumFunctions", i64 1}
!9 = !{!"DetailedSummary", !10}
!10 = !{!11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26}
!11 = !{i32 10000, i64 0, i32 0}
!12 = !{i32 100000, i64 0, i32 0}
!13 = !{i32 200000, i64 6, i32 1}
!14 = !{i32 300000, i64 6, i32 1}
!15 = !{i32 400000, i64 6, i32 1}
!16 = !{i32 500000, i64 6, i32 1}
!17 = !{i32 600000, i64 6, i32 1}
!18 = !{i32 700000, i64 6, i32 1}
!19 = !{i32 800000, i64 6, i32 1}
!20 = !{i32 900000, i64 6, i32 1}
!21 = !{i32 950000, i64 6, i32 1}
!22 = !{i32 990000, i64 6, i32 1}
!23 = !{i32 999000, i64 6, i32 1}
!24 = !{i32 999900, i64 6, i32 1}
!25 = !{i32 999990, i64 6, i32 1}
!26 = !{i32 999999, i64 6, i32 1}
!27 = !{i32 1, !"wchar_size", i32 4}
!28 = !{i32 7, !"PIC Level", i32 2}
!29 = !{!"clang version 9.0.0 (tags/RELEASE_900/final)"}
!30 = !{!"function_entry_count", i64 6}
!31 = !{!"branch_weights", i32 2, i32 6}
