/*
 * Copyright (c) 2013 Sviatoslav Chagaev <sviatoslav.chagaev@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef TREE_H
#define TREE_H

#include <gtk/gtk.h>

/* Some boilerplate GObject defines. 'klass' is used
 *   instead of 'class', because 'class' is a C++ keyword */

#define TYPE_TREE            (tree_get_type ())
#define TREE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_TREE, Tree))
#define TREE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  TYPE_TREE, TreeClass))
#define IS_TREE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), TYPE_TREE))
#define IS_TREE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  TYPE_TREE))
#define TREE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  TYPE_TREE, TreeClass))

/* The data columns that we export via the tree model interface */

enum {
	TREE_COL_DATA,
	TREE_N_COLUMNS,
};


typedef struct _TreeNode   TreeNode;
typedef struct _Tree       Tree;
typedef struct _TreeClass  TreeClass;

typedef int (*tree_walker_func_t)(TreeNode *, void *);


/* CustomRecord: this structure represents a row */

enum TreeNodeFlags {
	TREE_NODE_VISIBLE = 1,
	TREE_NODE_WALKED = 2,
};

struct _TreeNode {
	char			*data;
	char			*descr;
	struct _TreeNode	*parent;
	struct _TreeNode	*children;
	size_t			 nchildren;
	enum TreeNodeFlags	 flags;
};

/* CustomList: this structure contains everything we need for our
 *             model implementation. You can add extra fields to
 *             this structure, e.g. hashtables to quickly lookup
 *             rows or whatever else you might need, but it is
 *             crucial that 'parent' is the first member of the
 *             structure.                                          */

struct _Tree {
  GObject	 parent;      /* this MUST be the first member */
  TreeNode	*root;        /* a dynamically allocated array of pointers to
                                *   the CustomRecord structure for each row    */
  gint		 stamp;       /* Random integer to check whether an iter belongs to our model */
};



/* CustomListClass: more boilerplate GObject stuff */

struct _TreeClass {
	GObjectClass parent_class;
};


GType		 tree_get_type (void);

Tree		*tree_new (void);
TreeNode	*tree_vivify_child(TreeNode *parent, const char *data);
void		 tree_set_parents(TreeNode *parent);
void		 tree_print(TreeNode *node, size_t depth);
gboolean	 tree_get_iter_visible(GtkTreeModel *model, GtkTreeIter *iter, GtkTreePath *path);
void		 tree_clear(Tree *tree);
int		 tree_foreach_leaf(Tree *tree, tree_walker_func_t cb, void *data);

#endif 
