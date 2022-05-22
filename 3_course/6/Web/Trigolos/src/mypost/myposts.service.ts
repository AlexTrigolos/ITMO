import { Injectable } from '@nestjs/common';
import { PrismaClient } from '@prisma/client';
import { DeleteMyPostDto } from './dto/delete-mypost.dto';
import { CreateMyPostDto } from './dto/create-mypost.dto';
import { PublishMyPostDto } from './dto/publish-mypost.dto';
import { NewContentMyPostDto } from './dto/newContent-mypost.dto';

const prisma = new PrismaClient();

@Injectable()
export class MyPostsService {
  async create(myPost: CreateMyPostDto) {
    let IdNewMyPost;
    const a = await prisma.post.findMany({
      select: {
        id: true,
      },
    });
    const lst: number[] = [];
    for (let i = 0; i <= a.length; i++) {
      lst.push(i);
    }
    for (let i = 0; i < a.length; i++) {
      delete lst[a[i].id];
    }
    for (let i = 0; i <= a.length; i++) {
      if (lst[i] != undefined) {
        IdNewMyPost = lst[i];
        break;
      }
    }
    if (myPost.authorId === undefined) {
      return await prisma.post.create({
        data: {
          id: IdNewMyPost,
          title: myPost.title,
          content: myPost.content,
          published: false,
        },
        select: {
          id: true,
          title: true,
          content: true,
          published: true,
          author: true,
          authorId: true,
        },
      });
    } else {
      const rtn = await prisma.post.create({
        data: {
          id: IdNewMyPost,
          title: myPost.title,
          content: myPost.content,
          published: false,
          authorId: myPost.authorId,
        },
        select: {
          id: true,
          title: true,
          content: true,
          published: true,
          author: true,
          authorId: true,
        },
      });
      await prisma.user.update({
        where: {
          id: myPost.authorId,
        },
        data: {
          posts: {
            connect: {
              id: IdNewMyPost,
            },
          },
        },
      });
      return rtn;
    }
  }

  async findAll(page = 1) {
    return await prisma.post.findMany({
      skip: 5 * (page - 1),
      take: 5,
      select: {
        id: true,
        title: true,
        content: true,
        published: true,
        author: true,
        authorId: true,
      },
    });
  }

  async delete(deleteMyPostDto: DeleteMyPostDto) {
    return await prisma.post.delete({
      where: {
        id: deleteMyPostDto.id,
      },
      select: {
        id: true,
        title: true,
        content: true,
        published: true,
        author: true,
        authorId: true,
      },
    });
  }

  async publishMyPost(publishMyPostDto: PublishMyPostDto) {
    return await prisma.post.update({
      where: {
        id: publishMyPostDto.id,
      },
      data: {
        published: true,
      },
      select: {
        id: true,
        title: true,
        content: true,
        published: true,
        author: true,
        authorId: true,
      },
    });
  }

  async newContentMyPost(newContentMyPostDto: NewContentMyPostDto) {
    return await prisma.post.update({
      where: {
        id: newContentMyPostDto.id,
      },
      data: {
        content: newContentMyPostDto.content,
      },
      select: {
        id: true,
        title: true,
        content: true,
        published: true,
        author: true,
        authorId: true,
      },
    });
  }
}
