/*     */ package com.perfino.b.b;
/*     */ 
/*     */ import com.google.common.collect.Maps;
/*     */ import com.perfino.agent.config.recording.PerfinoProbe;
/*     */ import com.perfino.agent.config.transactions.TransactionType;
/*     */ import com.perfino.agent.i.c;
/*     */ import com.perfino.agent.m.a.b;
/*     */ import com.perfino.agent.m.i.a;
/*     */ import com.perfino.b.b.a.f;
/*     */ import com.perfino.data.transactions.TransactionTree;
/*     */ import java.util.ArrayList;
/*     */ import java.util.Collection;
/*     */ import java.util.Iterator;
/*     */ import java.util.List;
/*     */ import java.util.Map;
/*     */ import java.util.Map.Entry;
/*     */ import java.util.Set;
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ 
/*     */ class b
/*     */   implements i.a<TransactionTree>
/*     */ {
/*     */   b(a parama, TransactionTree paramTransactionTree, boolean paramBoolean) {}
/*     */   
/*     */   public boolean a(TransactionTree paramTransactionTree)
/*     */     throws Exception
/*     */   {
/*  75 */     if (paramTransactionTree != this.a) {
/*  76 */       a.a(this.c).a();
/*  77 */       a.b(this.c).b("name", paramTransactionTree.getName());
/*  78 */       if (a.c(this.c)) {
/*  79 */         a.d(this.c).a("time", a.a(this.c, paramTransactionTree.getTime()));
/*     */       }
/*  81 */       a.e(this.c).a("count", paramTransactionTree.getCount());
/*     */       
/*  83 */       TransactionType localTransactionType = paramTransactionTree.getTransactionType();
/*  84 */       if (localTransactionType != null) {
/*  85 */         a.f(this.c).b("type", localTransactionType.name().toLowerCase());
/*     */       }
/*     */       Object localObject1;
/*  88 */       if (a.g(this.c)) {
/*  89 */         localObject1 = paramTransactionTree.getPolicyType();
/*  90 */         if (localObject1 != a.b.a) {
/*  91 */           a.h(this.c).b("policy", ((a.b)localObject1).toString().toLowerCase());
/*  92 */           if (localObject1 == a.b.e) {
/*  93 */             a.i(this.c).b("error", paramTransactionTree.getPolicyTypeString());
/*     */           }
/*     */         }
/*     */       } else {
/*  97 */         a.j(this.c).b("policy", paramTransactionTree.getVerbosePolicyType(true));
/*     */       }
/*     */       
/* 100 */       if (paramTransactionTree.getPayloadCount() > 0) {
/* 101 */         localObject1 = Maps.newTreeMap();
/* 102 */         for (Iterator localIterator = paramTransactionTree.getPayloads().iterator(); localIterator.hasNext();) { localObject2 = (c)localIterator.next();
/* 103 */           localObject3 = PerfinoProbe.getByType(((c)localObject2).b());
/* 104 */           localObject4 = localObject3 == null ? "custom" + ((c)localObject2).b() : ((PerfinoProbe)localObject3).name().toLowerCase();
/* 105 */           Object localObject5 = (List)((Map)localObject1).get(localObject4);
/* 106 */           if (localObject5 == null) {
/* 107 */             localObject5 = new ArrayList();
/* 108 */             ((Map)localObject1).put(localObject4, localObject5);
/*     */           }
/* 110 */           ((List)localObject5).add(localObject2); }
/*     */         Object localObject2;
/*     */         Object localObject3;
/*     */         Object localObject4;
/* 114 */         a.k(this.c).b("payload");
/* 115 */         for (localIterator = ((Map)localObject1).entrySet().iterator(); localIterator.hasNext();) { localObject2 = (Map.Entry)localIterator.next();
/* 116 */           a.l(this.c).c((String)((Map.Entry)localObject2).getKey());
/* 117 */           for (localObject3 = a.a(this.c, (List)((Map.Entry)localObject2).getValue()).iterator(); ((Iterator)localObject3).hasNext();) { localObject4 = (c)((Iterator)localObject3).next();
/* 118 */             this.c.a((c)localObject4, this.b);
/*     */           }
/* 120 */           a.m(this.c).c();
/*     */         }
/* 122 */         a.n(this.c).d();
/*     */       }
/*     */     }
/* 125 */     if (paramTransactionTree.getChildCount() > 0) {
/* 126 */       a.o(this.c).c("children");
/*     */     }
/* 128 */     return true;
/*     */   }
/*     */   
/*     */   public void b(TransactionTree paramTransactionTree) throws Exception
/*     */   {
/* 133 */     if (paramTransactionTree.getChildCount() > 0) {
/* 134 */       a.p(this.c).c();
/*     */     }
/* 136 */     if (paramTransactionTree != this.a) {
/* 137 */       a.q(this.c).d();
/*     */     }
/*     */   }
/*     */ }


/* Location:              F:\TDDOWNLOAD\perfino-server.jar!\com\perfino\b\b\b.class
 * Java compiler version: 7 (51.0)
 * JD-Core Version:       0.7.1
 */